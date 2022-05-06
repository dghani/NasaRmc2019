#include <tfr_mission_control/ui_mission_control.h>


#include <cstddef>
#include <mutex>

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QScrollBar>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QKeyEvent>

namespace tfr_mission_control {

	class ArmTab : public QWidget{
		
		Q_OBJECT

		public:
			ArmTab();
			~ArmTab();
			void setupSignalsAndSlotss();
			void pressButton();


		private:
			QWidget* widget;




	};





}