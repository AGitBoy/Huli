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
	
	settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
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

void WebPage::authenticationRequiredProxyHandler(const QUrl &srcUrl, QAuthenticator* authenticator, const QString &proxyHost) {
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
		QDialog certificateDialog(window);
		certificateDialog.setModal(true);
		
		certificateDialog.setWindowTitle("Certificate Error");
		
		QGridLayout grid;
		
		QLabel iconLabel;
		QIcon labelIcon = QIcon::fromTheme("security-low"); // todo: add fallback icon
		iconLabel.setPixmap(labelIcon.pixmap(64));
		
		grid.addWidget(&iconLabel, 0, 0);
		
		QLabel textLabel;
		textLabel.setText(error.errorDescription());
		
		grid.addWidget(&textLabel, 0, 1);
		
		auto* box = new QDialogButtonBox(QDialogButtonBox::Abort | QDialogButtonBox::Ignore, &certificateDialog);
		
		QPushButton* AbortButton = box->button(QDialogButtonBox::Abort);
		AbortButton->setDefault(true);
		AbortButton->setAutoDefault(true);
		
		QPushButton* IgnoreButton = box->button(QDialogButtonBox::Ignore);
		IgnoreButton->setDefault(false);
		IgnoreButton->setAutoDefault(false);
		
		grid.addWidget(box, 1, 0, 1, 2);
		
		connect(
			box, &QDialogButtonBox::accepted,
			&certificateDialog, &QDialog::accept
		);
		
		connect(
			box, &QDialogButtonBox::rejected,
			&certificateDialog, &QDialog::reject
		);
		
		certificateDialog.setLayout(&grid);
		
		return certificateDialog.exec() == QDialog::Accepted;
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
	
	
	QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &authDialog);
	
	connect(box, &QDialogButtonBox::accepted, &authDialog, &QDialog::accept);
	connect(box, &QDialogButtonBox::rejected, &authDialog, &QDialog::reject);
	
	auto*vBox(new QVBoxLayout());
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
