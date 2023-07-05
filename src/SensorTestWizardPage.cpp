#include "SensorTestWizardPage.h"
#include "ui_SensorTestWizardPage.h"

#include <QTimer>


#ifdef WALLABY
#include <wallaby/general.h>
#include <wallaby/analog.h>
#else
#include <kovan/general.h>
#include <kovan/analog.h>
#endif

SensorTestWizardPage::SensorTestWizardPage(QWidget *parent)
	: QWizardPage(parent),
	ui(new Ui::SensorTestWizardPage),
	m_timer(new QTimer(this))
{
	ui->setupUi(this);
	
	connect(m_timer, SIGNAL(timeout()), SLOT(update()));
	m_plot = ui->plot->addPlot(Qt::black);
}

SensorTestWizardPage::~SensorTestWizardPage()
{
	delete ui;
}

void SensorTestWizardPage::initializePage()
{
	m_timer->start(25);
}

void SensorTestWizardPage::cleanupPage()
{
	m_timer->stop();
}

void SensorTestWizardPage::update()
{
	publish();
	ui->plot->push(m_plot, analog10(0));
	ui->plot->inc();
}
