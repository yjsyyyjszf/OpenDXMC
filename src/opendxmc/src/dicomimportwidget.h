/*This file is part of OpenDXMC.

OpenDXMC is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenDXMC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenDXMC. If not, see < https://www.gnu.org/licenses/>.

Copyright 2019 Erlend Andersen
*/

#pragma once

#include "material.h"

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <vtkSmartPointer.h>
#include <vtkDICOMDirectory.h>

#include <vector>
#include <array>


class DicomImportWidget : public QWidget
{
	Q_OBJECT
public:
	DicomImportWidget(QWidget *parent = nullptr);

signals:
	void dicomFolderSelectedForBrowsing(QString folderPath);
	void dicomSeriesActivated(QStringList filePaths);
	void blurRadiusChanged(const double*);
	void outputSpacingChanged(const double*);
	void useOutputSpacingChanged(bool value);
	void aqusitionVoltageChanged(double voltage);
	void aqusitionAlFiltrationChanged(double mm);
	void aqusitionCuFiltrationChanged(double mm);
	void segmentationMaterialsChanged(const std::vector<Material>& materials);

private:
	void browseForFolder(void);
	void lookInFolder(void);
	void lookInFolder(QString folderPath);
	void seriesActivated(int index);


	QLineEdit *m_browseLineEdit;
	vtkSmartPointer<vtkDICOMDirectory> m_imageDirectorySnooper;
	QComboBox *m_seriesSelector;

	std::array<double, 3> m_outputSpacing = { 2, 2, 2 };
	std::array<double, 3> m_blurRadius = { 1, 1, 1 };
	bool m_useOutputSpacing = false;
};
