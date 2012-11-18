#include "BusyIndicator.h"
#include "RootController.h"
#include "MechanicalStyle.h"
#include "HomeWidget.h"
#include "StatusBar.h"
#include "KovanDevice.h"
#include "SimulatorDevice.h"
#include "FirstRunWizard.h"
#include "FactoryWidget.h"

#include <QApplication>
#include <QDir>

int main(int argc, char* argv[])
{
	QApplication::setStyle(new MechanicalStyle);
	QApplication app(argc, argv);
	
	QDir::setCurrent(QApplication::applicationDirPath());
	qmlRegisterType<BusyIndicator>("ZapBsComponents", 1, 0, "BusyIndicator");
	
	srand(time(NULL));
	
	Kovan::Device device;
	if(device.isTouchscreen()) {
		app.setOverrideCursor(QCursor(Qt::BlankCursor));
	}
	//RootController::ref().presentQml(QUrl::fromLocalFile("loading.qml"));
	RootController::ref().presentWidget(new HomeWidget(&device));
	RootController::ref().presentWidget(new FactoryWidget(&device));
	
	return app.exec();
}