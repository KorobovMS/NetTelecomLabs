#include "emailwidget.h"

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

EmailWidget::EmailWidget(const Email& email, QWidget *parent) :
    QWidget(parent),
    email_(email)
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QFormLayout* info = new QFormLayout;
    QLabel* from_label = new QLabel("From:");
    QLineEdit* from = new QLineEdit(email_.headers["From"]);
    info->addRow(from_label, from);
    QLabel* to_label = new QLabel("To:");
    QLineEdit* to = new QLineEdit(email_.headers["To"]);
    info->addRow(to_label, to);
    QLabel* subject_label = new QLabel("Subject:");
    QLineEdit* subject = new QLineEdit(email_.headers["Subject"]);
    info->addRow(subject_label, subject);

    QLineEdit* body = new QLineEdit(email_.body);

    main_layout->addLayout(info);
    main_layout->addWidget(body);
}

const Email& EmailWidget::GetEmail() const
{
    return email_;
}
