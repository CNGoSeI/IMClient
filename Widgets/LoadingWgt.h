#ifndef LOADINGWGT_H
#define LOADINGWGT_H

#include "Common/SingletonTemplate.h"
#include "Common/LoadUIWgtBase.h"

class QDialog;
class QMovie;
class QLabel;

class SLoadingWgt:public ILoadUIWgtBase
{

public:
	~SLoadingWgt() override =default;
	static SLoadingWgt& Instance();
	void PopShow(QWidget* Parent);
	void HideStop();

private:
	SLoadingWgt();

protected:
	void InitControls() override;

private:
	QLabel* Lab_Moive{ nullptr };
	QMovie* Movie{ nullptr };
};

#endif // LOADINGWGT_H
