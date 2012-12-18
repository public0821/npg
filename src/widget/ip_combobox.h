/*
 * ip_combobox.h
 *
 *  Created on: 2012-12-18
 *      Author: Young <public0821@gmail.com>
 */

#ifndef IP_COMBOBOX_H_
#define IP_COMBOBOX_H_

#include <qcombobox.h>
#include "lib/socket/ip_address.h"

class IpComboBox: public QComboBox {
public:
	IpComboBox(QWidget*parent);
	virtual ~IpComboBox();
public:
	IpAddress getIpAddress();
};

#endif /* IP_COMBOBOX_H_ */
