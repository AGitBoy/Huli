#include "WebPage.h"
#include "iconProvider.h"

WebPage::WebPage(
    QWebEngineProfile* profile,
    QObject* parent
)
    : QWebEnginePage(profile, parent)
{
    connect(
        this, &QWebEnginePage::authenticationRequired,
        this, &WebPage::authenticationRequiredHandler
    );
    
    connect(
        this, &QWebEnginePage::proxyAuthenticationRequired,
        this, &WebPage::authenticationRequiredProxyHandler
    );
#if QT_11_SUPPORT
    connect(
        this, &QWebEnginePage::registerProtocolHandlerRequested,
        this, &WebPage::registerProtocolHandler
    );
#endif
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

#if QT_11_SUPPORT
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
#endif

QStringList WebPage::chooseFiles(
    QWebEnginePage::FileSelectionMode mode,
    const QStringList &oldFiles,
    const QStringList &acceptedMimeTypes) {
    
    QFileDialog::FileMode dialogMode;
    if(mode == QWebEnginePage::FileSelectOpen) {
        dialogMode = QFileDialog::ExistingFile;
    } else {
        dialogMode = QFileDialog::ExistingFiles;
    }
    
    QFileDialog* dialog = new QFileDialog();
    
    dialog->setFileMode(dialogMode);

    QStringList mimeFilters = acceptedMimeTypes;
    mimeFilters << "application/octet-stream";
    
    dialog->setMimeTypeFilters(mimeFilters);
    
    QStringList selectedFiles;
    if(dialog->exec()) {
        selectedFiles = dialog->selectedFiles();
    }
    
    return selectedFiles;
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
    } else {
        QMessageBox::critical(window, "Certificate Error", error.errorDescription(), QMessageBox::Ok);
        return false;
    }
}

void WebPage::makeDialog(QAuthenticator* authenticator, const QString &labelText) {
    QWidget* window = view()->window();
    
    QDialog authDialog(window);
    authDialog.setModal(true);
    
    auto* grid = new QGridLayout();
    
    QIcon labelIcon = iconProvider::getSecurityIcon();
    
    QLabel textLabel(labelText);
    QLabel iconLabel;
    
    iconLabel.setPixmap(labelIcon.pixmap(64));
    
    textLabel.setWordWrap(true);
    
    grid->addWidget(&iconLabel, 0, 0);
    grid->addWidget(&textLabel, 0, 1);
    
    QLabel usernameLabel(fontUtils::setTextColor(
        tr("Username: "),
        textLabel.palette().color(QPalette::Disabled, QPalette::Text)
    ));
    
    QLineEdit usernameInput;
    
    grid->addWidget(&usernameLabel, 1, 0);
    grid->addWidget(&usernameInput, 1, 1);
    
    QLabel passwordLabel(fontUtils::setTextColor(
        tr("Password: "),
        textLabel.palette().color(QPalette::Disabled, QPalette::Text)
    ));
    
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
