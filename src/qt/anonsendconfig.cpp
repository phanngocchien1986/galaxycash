#include "anonsendconfig.h"
#include "ui_anonsendconfig.h"

#include "galaxycashunits.h"
#include "guiconstants.h"
#include "optionsmodel.h"
#include "walletmodel.h"
#include "init.h"

#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include <QSettings>

AnonsendConfig::AnonsendConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnonsendConfig),
    model(0)
{
    ui->setupUi(this);

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

AnonsendConfig::~AnonsendConfig()
{
    delete ui;
}

void AnonsendConfig::setModel(WalletModel *model)
{
    this->model = model;
}

void AnonsendConfig::clickBasic()
{
    configure(true, nAnonymizeAmount, 2);

    QString strAmount(GalaxyCashUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), nAnonymizeAmount));
    QMessageBox::information(this, tr("Anonsend Configuration"),
        tr(
            "Anonsend was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening 's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void AnonsendConfig::clickHigh()
{
    configure(true, nAnonymizeAmount, 8);

    QString strAmount(GalaxyCashUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), nAnonymizeAmount));
    QMessageBox::information(this, tr("Anonsend Configuration"),
        tr(
            "Anonsend was successfully set to high (%1 and 8 rounds). You can change this at any time by opening 's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void AnonsendConfig::clickMax()
{
    configure(true, nAnonymizeAmount, 16);

    QString strAmount(GalaxyCashUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), nAnonymizeAmount));
    QMessageBox::information(this, tr("Anonsend Configuration"),
        tr(
            "Anonsend was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening Bitcoin's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void AnonsendConfig::configure(bool enabled, int coins, int rounds) {

    QSettings settings;

    settings.setValue("nAnonsendRounds", rounds);
    settings.setValue("nAnonymizeAmount", coins);

    nAnonsendRounds = rounds;
    nAnonymizeAmount = coins;
}
