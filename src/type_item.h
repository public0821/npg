#ifndef TYPE_ITEM_H
#define TYPE_ITEM_H

#include <QtGui/QWidget>

class TypeItem : public QWidget
{
    Q_OBJECT

public:
    TypeItem(const QIcon& icon, const QString& text, QWidget *parent = 0);
    ~TypeItem();

private:
};

#endif // TYPE_ITEM_H
