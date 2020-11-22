/*
 * Copyright (C) 2014 - 2020 Christian Hohnstaedt.
 *
 * All rights reserved.
 */

#ifndef __BUILTIN_EC_CURVES_H
#define __BUILTIN_EC_CURVES_H

#include <QString>
#include <QList>

#include "base.h"

#define CURVE_X962  1
#define CURVE_OTHER 2
#define CURVE_RFC5480 3

class builtin_curve
{
    public:
	int nid;
	QString comment;
	unsigned order_size;
	int flags;
	/* type: CKF_EC_F_P || CKF_EC_F_2M */
	unsigned long type;
	builtin_curve(int n, QString c, int s, int f, int t) {
		nid = n;
		comment = c;
		order_size = s;
		flags = f;
		type = t;
	};
};

class builtin_curves: public QList<builtin_curve>
{
    public:
	builtin_curves();
	bool containNid(int nid)
	{
		foreach(const builtin_curve &c, *this)
			if (c.nid == nid)
				return true;
		return false;
	}
};

#endif
