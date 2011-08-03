#include "npg.h"

npg::npg(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
//	ui.horizontalLayout
	QSize size = this->size();
	ui.horizontalLayoutWidget->setGeometry(QRect(0, 0, size.height(), size.width()));
}

npg::~npg()
{

}
