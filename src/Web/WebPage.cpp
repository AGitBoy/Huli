#include "WebPage.h"

WebPage::WebPage(QWebEngineProfile* profile, QObject* parent): QWebEnginePage(profile, parent) {
	connect(
		this, &QWebEnginePage::authenticationRequired,
		this, &WebPage::authenticationRequiredHandler
	);
	
	connect(
		this, &QWebEnginePage::proxyAuthenticationRequired,
		this, &WebPage::authenticationRequiredProxyHandler
	);
	
	connect(
		this, &QWebEnginePage::registerProtocolHandlerRequested,
		this, &WebPage::registerProtocolHandler
	);
	
}

void WebPage::authenticationRequiredHandler(const QUrl &srcUrl, QAuthenticator* authenticator) {
	QString labelText(
		QString("Enter credentials for '%1' the site says '%2'").arg(
			srcUrl.toString().toHtmlEscaped(),
			authenticator->realm()
		)
	);
	
	makeDialog(authenticator, labelText);
}

void WebPage::authenticationRequiredProxyHandler(const QUrl &srcUrl, QAuthenticator* authenticator,
                                                 const QString &proxyHost) {
	QString labelText(QString("Connect to proxy \"%1\" using: ").arg(proxyHost));
	
	makeDialog(authenticator, labelText);
}

void WebPage::registerProtocolHandler(QWebEngineRegisterProtocolHandlerRequest request) {
	auto answer = QMessageBox::question(
		view()->window(),
		"Permission Request",
		tr("Allow %1 to open %2 links?").arg(request.origin().host(), request.scheme())
	);
	
	if(answer == QMessageBox::Yes) {
		request.accept();
	} else {
		request.reject();
	}
}

bool WebPage::certificateError(const QWebEngineCertificateError &error) {
	QWidget* window = view()->window();
	if(error.isOverridable()) {
		return QMessageBox::warning(
			window,
			"Certificate Error",
			error.errorDescription(),
			QMessageBox::Abort | QMessageBox::Ignore
		) == QMessageBox::Ignore;
	}
	
	return false;
}

void WebPage::makeDialog(QAuthenticator* authenticator, const QString &labelText) {
	QWidget* window = view()->window();
	
	QDialog authDialog(window);
	authDialog.setModal(true);
	
	auto* grid = new QGridLayout();
	
	QIcon labelIcon = QIcon::fromTheme("dialog-password"); // todo: add fallback icon
	
	QLabel textLabel(labelText);
	QLabel iconLabel;
	
	iconLabel.setPixmap(labelIcon.pixmap(64));
	
	textLabel.setWordWrap(true);
	
	grid->addWidget(&iconLabel, 0, 0);
	grid->addWidget(&textLabel, 0, 1);
	
	QLabel usernameLabel("Username:");
	QLineEdit usernameInput;
	
	grid->addWidget(&usernameLabel, 1, 0);
	grid->addWidget(&usernameInput, 1, 1);
	
	QLabel passwordLabel("Password:");
	QLineEdit passwordInput;
	passwordInput.setEchoMode(QLineEdit::Password);
	
	grid->addWidget(&passwordLabel, 2, 0);
	grid->addWidget(&passwordInput, 2, 1);
	
	
	QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &authDialog);
	
	connect(box, &QDialogButtonBox::accepted, &authDialog, &QDialog::accept);
	connect(box, &QDialogButtonBox::rejected, &authDialog, &QDialog::reject);
	
	auto* vBox(new QVBoxLayout());
	vBox->addLayout(grid);
	vBox->addWidget(box);
	
	authDialog.setLayout(vBox);
	
	if(authDialog.exec() == QDialog::Accepted) {
		authenticator->setUser(usernameInput.text());
		authenticator->setPassword(passwordInput.text());
	} else {
		*authenticator = QAuthenticator();
	}
}
