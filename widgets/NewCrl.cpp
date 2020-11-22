/* vi: set sw=4 ts=4:
 *
 * Copyright (C) 2010 - 2011 Christian Hohnstaedt.
 *
 * All rights reserved.
 */


#include "NewCrl.h"
#include "lib/base.h"
#include "lib/func.h"
#include "widgets/validity.h"
#include "widgets/MainWindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>

NewCrl::NewCrl(QWidget *parent, const crljob &j)
	:QWidget(parent), task(j)
{
	pki_x509 *issuer = task.issuer;
	pki_key *key = issuer->getRefKey();

	setupUi(this);
	dateBox->setTitle(issuer->getIntName());
	validNumber->setText(QString::number(task.crlDays));
	validRange->setCurrentIndex(0);
	on_applyTime_clicked();
	nextUpdate->setEndDate(true);

	hashAlgo->setKeyType(key->getKeyType());
	hashAlgo->setupHashes(key->possibleHashNids());
	hashAlgo->setCurrentMD(task.hashAlgo);

	crlNumber->setText(task.crlNumber.toDec());
	if (issuer->hasExtension(NID_subject_alt_name)) {
		subAltName->setEnabled(true);
		subAltName->setChecked(task.subAltName);
	} else {
		subAltName->setEnabled(false);
	}
	revocationReasons->setChecked(task.withReason);
	authKeyId->setChecked(task.authKeyId);
}

crljob NewCrl::getCrlJob() const
{
	crljob t = task;
	t.withReason = revocationReasons->isChecked();
	t.authKeyId = authKeyId->isChecked();
	t.subAltName = subAltName->isChecked();
	t.setCrlNumber = setCrlNumber->isChecked();
	t.lastUpdate = lastUpdate->getDate();
	t.nextUpdate = nextUpdate->getDate();
	return t;
}

void NewCrl::on_applyTime_clicked()
{
	nextUpdate->setDiff(lastUpdate, validNumber->text().toInt(),
					validRange->currentIndex());
}

NewCrl::~NewCrl()
{
	qDebug() << "NewCrl::~NewCrl() -- DELETED";
}
