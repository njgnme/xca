/* vi: set sw=4 ts=4:
 *
 * Copyright (C) 2001 - 2012 Christian Hohnstaedt.
 *
 * All rights reserved.
 */


#ifndef __NEWX509_H
#define __NEWX509_H

#include "ui_NewX509.h"
#include "lib/oid.h"
#include "lib/db.h"
#include "kvView.h"
#include "MainWindow.h"
#include <openssl/x509v3.h>
#include <QListWidget>

class MainWindow;
class extList;
class pki_temp;
class pki_x509req;
class pki_x509super;
class pki_x509;
class pki_key;
class QPixmap;
class QListbox;
class x509name;
class x509v3ext;
class extList;

class nameEdit {
    public:
	int nid;
	QLineEdit *edit;
	QLabel *label;
	nameEdit(int n, QLineEdit *e, QLabel *l) {
		nid = n; edit = e; label = l;
	}
};

class NewX509: public QDialog, public Ui::NewX509
{
		Q_OBJECT
	private:
		NIDlist aia_nid;
		NIDlist attr_nid;
		QList<nameEdit> attrEdits;
		QList<nameEdit> nameEdits;
		X509V3_CTX ext_ctx;
		void editV3ext(QLineEdit *le, QString types, int n);
		enum pki_type pt;
		enum pki_source pkiSource;
		void templateChanged(QString templatename);
		QString mandatoryDnRemain();
		QStringList tabnames;
		QList<pki_key*> unusedKeys, allKeys;
		pki_x509 *ctx_cert;
		QString v3ext_backup;
		kvmodel *extDNmodel;
		extList getExtDuplicates();
		void checkIcon(const QString &text, int nid, QLabel*img);
		void selfComment(QString msg);
		QMap<QString, QLineEdit*> templateLineEdits;
		QMap<QString, QCheckBox*> templateCheckBoxes;
		pki_temp *caTemplate(pki_x509 *ca) const;
		void setupExplicitDN(NIDlist my_dn_nid);
		QList<nameEdit> setupExplicitInputs(NIDlist nid_list,
                        QWidget *parent, QWidget *old, int columns);

	public:
		NewX509(QWidget *parent);
		virtual ~NewX509();
		void initCtx();
		void setRequest(); // reduce to request form
		void setTemp(pki_temp *temp); // reduce to template form
		void setCert(); // reduce to certificate form
		void toTemplate(pki_temp *temp);
		void fromTemplate(pki_temp *temp);
		void defineTemplate(pki_temp *temp);
		void defineRequest(pki_x509req *req);
		void defineSigner(pki_x509 *defcert, bool applyTemp);
		void fromX509super(pki_x509super *cert_or_req, bool applyTemp);
		void templateChanged(pki_temp *templ);
		pki_key *getSelectedKey();
		pki_x509 *getSelectedSigner();
		pki_x509req *getSelectedReq();
		x509name getX509name(int _throw = 0);
		void setX509name(const x509name &n);
		x509v3ext getBasicConstraints();
		x509v3ext getSubKeyIdent();
		x509v3ext getAuthKeyIdent();
		x509v3ext getOCSPstaple();
		x509v3ext getKeyUsage();
		x509v3ext getEkeyUsage();
		x509v3ext getSubAltName();
		x509v3ext getIssAltName();
		x509v3ext getCrlDist();
		x509v3ext getAuthInfAcc();
		extList getGuiExt();
		extList getNetscapeExt();
		extList getAdvanced();
		extList getAllExt();
		void setupTmpCtx();
		void initCtx(pki_x509 *subj, pki_x509 *iss, pki_x509req *req);
		void switchHashAlgo();
		void setReqAttributes(pki_x509req *req);
		void getReqAttributes(pki_x509req *req);
		int checkExtDuplicates();
		void subjectFromTemplate(pki_temp *temp);
		void extensionsFromTemplate(pki_temp *temp);
		pki_temp *currentTemplate();
		void gotoTab(int tab);
		void setupLineEditByNid(int nid, QLineEdit *l);
		int validateExtensions(QString nconf, QString &result);
		int do_validateExtensions();
		void undo_validateExtensions();
		enum pki_source getPkiSource() const;
		QList<pki_x509req*> getAllRequests() const;
		QList<pki_x509*> getAllIssuers() const;
		QList<pki_temp*> getAllTempsAndPredefs() const;
		QList<pki_key*> getUnusedKeys() const;
		QList<pki_key*> getAllKeys() const;

	public slots:
		void on_fromReqCB_clicked();
		void on_keyList_currentIndexChanged(const QString &);
		void on_reqList_currentIndexChanged(const QString &);
		void newKeyDone(pki_key *nkey);
		void on_applyTime_clicked();
		void on_editSubAlt_clicked();
		void on_editIssAlt_clicked();
		void on_editCrlDist_clicked();
		void on_editAuthInfAcc_clicked();
		void on_foreignSignRB_toggled(bool checked);
		void on_genKeyBut_clicked();
		void on_showReqBut_clicked();
		void on_certList_currentIndexChanged(int index);
		void on_applyTemplate_clicked();
		void on_applySubject_clicked();
		void on_applyExtensions_clicked();
		void on_adv_validate_clicked();
		void on_usedKeysToo_toggled(bool checked);
		void on_tabWidget_currentChanged(int idx);
		void on_reqSubChange_clicked();
		void accept();
		void itemChanged(pki_base*);
		void setupExtDNwidget(const QString &s, QLineEdit *w);
		void checkSubAltName(const QString & text);
		void checkIssAltName(const QString & text);
		void checkCrlDist(const QString & text);
		void checkAuthInfAcc(const QString & text);

	signals:
		void genKey(QString);
		void showReq(pki_base *req);
};

#endif
