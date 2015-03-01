#ifndef EMAILWIDGET_H
#define EMAILWIDGET_H

#include <QHash>
#include <QString>
#include <QWidget>

#include "email.h"

class EmailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmailWidget(const Email& email, QWidget *parent = 0);
    const Email& GetEmail() const;

signals:
    void OnClick(EmailWidget* self);
    void OnDelete(EmailWidget* self);

private:
    Email email_;
};

#endif // EMAILWIDGET_H
