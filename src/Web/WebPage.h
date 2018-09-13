#ifndef HULI_WEBPAGE_H
#define HULI_WEBPAGE_H

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "fontUtils.h"

class WebPage: public QWebEnginePage {
Q_OBJECT;

public:
	explicit WebPage(QWebEngineProfile* profile, QObject* parent = nullptr);

public slots:
	void authenticationRequiredHandler(const QUrl &srcUrl, QAuthenticator* authenticator);
	void authenticationRequiredProxyHandler(const QUrl &srcUrl, QAuthenticator* authenticator, const QString &proxyHost);
	void registerProtocolHandler(QWebEngineRegisterProtocolHandlerRequest request);

private:
	void makeDialog(QAuthenticator* authenticator, const QString &labelText);
	
protected slots:
	QStringList chooseFiles(QWebEnginePage::FileSelectionMode mode, const QStringList &oldFiles, const QStringList &acceptedMimeTypes) override;

protected:
	bool certificateError(const QWebEngineCertificateError &error) override;
};

#endif //HULI_WEBPAGE_H
