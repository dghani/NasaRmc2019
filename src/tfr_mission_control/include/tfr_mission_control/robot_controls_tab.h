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

	class RobotControlsTab : public QWidget {
		Q_OBJECT

		public:
			RobotControlsTab();
			~RobotControlsTab();
			void setupSignalsAndSlots();
			void setButtonAvailability(bool availability);


		protected slots:
			void armStoringPos();
			void armMiningPos();
			void armDumpingPos();
			void armFaceForwards();

			void turntableStoringPos();
			void turntableMiningPos();
			void turntableDumpingPos();
			void turntableFaceForwards();

			void binDumpingPos();
			void binCollectionPos();

			void drivetrainPresetForwards();
			void drivetrainPresetBackwards();
			void drivetrainPresetTurnLeft();
			void drivetrainPresetTurnRight();


			void extendUpperArm();
			void retractUpperArm();

			void extendLowerArm();
			void retractLowerArm();

			void extendScoop();
			void retractScoop();

			void turntableRotateLeft();
			void turntableRotateRight();

			void binExtend();
			void binRetract();

			void drivetrainMoveForwards();
			void drivetrainMoveBackwards();
			void drivetrainTurnLeft();
			void drivetrainTurnRight();
			void drivetrainMoveLeftTread();
			void drivetrainMoveRightTread();


	};





}