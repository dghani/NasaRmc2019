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
			void setupSignalsAndSlots();
			void setButtonAvailability(bool availability);


		private:
			QWidget* widget;


		protected slots:
			void startingPosition();
			void miningPosition();
			void dumpingPosition();
			void faceFowards();

			void upperArmExtend();
			void upperArmRetract();
			void lowerArmExtend();
			void lowerArmRetract();
			void scoopExtend();
			void scoopRetract();




	};





}