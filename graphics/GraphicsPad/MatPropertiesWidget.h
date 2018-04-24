#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>
#include <QtGui\qlineedit.h>

class Material;

class MatPropertiesWidget : public QWidget
{
	Q_OBJECT

public:
	MatPropertiesWidget(Material* mat, QWidget* parent = 0);
	~MatPropertiesWidget();

	friend class ObjPropertiesManager;

	/*QLabel* getKa_map();
	QLabel* getKd_map();
	QLabel* getKs_map();*/

protected:
	Material* material;

private:
	QVBoxLayout* MainLayout;
	QLabel* FileTypeLabel;
	QHBoxLayout* NameLayout;
	QLabel* NameLabel;
	QLabel* matName;

	QHBoxLayout* VShaderLayout;
	QLabel * VShaderLabel;
	QLineEdit* VertexShader;

	QHBoxLayout* FShaderLayout;
	QLabel * FShaderLabel;
	QLineEdit* FragmentShader;

	QHBoxLayout* KaLayout;
	QLabel * KaLabel;
	QLineEdit* Ka0;
	QLineEdit* Ka1;
	QLineEdit* Ka2;

	QHBoxLayout* KdLayout;
	QLabel * KdLabel;
	QLineEdit* Kd0;
	QLineEdit* Kd1;
	QLineEdit* Kd2;

	QHBoxLayout* KsLayout;
	QLabel * KsLabel;
	QLineEdit* Ks0;
	QLineEdit* Ks1;
	QLineEdit* Ks2;

	QHBoxLayout* NsLayout;
	QLabel * NsLabel;
	QLineEdit* Ns;

	QHBoxLayout* Ka_mapLayout;
	QLabel * Ka_mapLabel;
	QLabel* Ka_map;

	QHBoxLayout* Kd_mapLayout;
	QLabel * Kd_mapLabel;
	QLabel* Kd_map;

	QHBoxLayout* Ks_mapLayout;
	QLabel * Ks_mapLabel;
	QLabel* Ks_map;

	void _CreateVertexShader();
	void _CreateFragmentShader();

	void _CreateAmbientColor();
	void _CreateDiffuseColor();
	void _CreateSpecularColor();
	void _CreateSpecularExp();
	void _CreateAmbientTexture();
	void _CreateDiffuseTexture();
	void _CreateSpecularTexture();

private slots:
	
	void _KaChanged();
	void _KdChanged();
	void _KsChanged();
	void _NsChanged();
	void _mapKaChanged();
	void _mapKdChanged();
	void _mapKsChanged();
	void _ShaderChanged();

};