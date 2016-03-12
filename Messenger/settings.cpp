#include "settings.h"

Settings::Settings(QSettings *s, QWidget *parent) :
    QMainWindow(parent), set(s)
{
    QFormLayout *forms = new QFormLayout;
    QVBoxLayout *main = new QVBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *save = new QPushButton("Save"),
                *cancel = new QPushButton("Cancel"),
                *ok = new QPushButton("OK");
    keepAvile = new QCheckBox("Turn on KeepAvile");
    nick = new QLineEdit;
    port = new QSpinBox;
    setKeepAvile = new QSpinBox;

   // keepAvile->setCheckState(s->value("keepAvile").toInt());

    connect(save, SIGNAL(clicked()), SLOT(writeSettings()));
    connect(cancel,SIGNAL(clicked()), SLOT(close()));
    connect(ok, SIGNAL(clicked()), SLOT(writeAndClose()));

    buttons->addWidget(ok);
    buttons->addWidget(cancel);
    buttons->addWidget(save);

    forms->addRow("You Nick:", nick);
    forms->addRow("Port:", port);
    forms->addRow("Keep Alive(R) Technology(ms)", keepAvile);
    forms->addRow("Period:", setKeepAvile);


    forms->setRowWrapPolicy(QFormLayout::DontWrapRows);
    forms->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    forms->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    forms->setLabelAlignment(Qt::AlignLeft);

    port->setRange(0,64000);
    nick->setText(s->value("nick").toString());
    port->setValue(s->value("port").toInt());
    setKeepAvile->setRange(0,5000);
    setKeepAvile->setValue(s->value("setkeepalive").toInt());
    keepAvile->setCheckState(s->value("keepAvile").toBool() ? Qt::Checked: Qt::Unchecked);

    main->addLayout(forms);
    main->addLayout(buttons);

    QWidget *w = new QWidget;
    w->setLayout(main);
    setCentralWidget(w);
}

void Settings::writeSettings()
{
    set->setValue("nick", nick->text());
    set->setValue("port", port->text().toInt());
    set->setValue("setkeepalive", setKeepAvile->text());
    set->setValue("keepAvile", keepAvile->isChecked());
    emit settingChange();
}

void Settings::writeAndClose()
{
    writeSettings();
    close();
}
