
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

#include "opendxmc/progresswidget.h"
#include "opendxmc/colormap.h"
#include <QVBoxLayout>
#include <QImage>
#include <QGraphicsScene>
#include <QTransform>
#include <QPixmap>
#include <QColor>
#include <QBrush>
#include <QTransform>

ProgressWidget::ProgressWidget(QWidget* parent) 
	: QWidget(parent)
{
	auto mainLayout = new QVBoxLayout(this);
	//mainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);
	m_view = new QGraphicsView(this);
	auto scene = new QGraphicsScene(m_view);
	m_view->setScene(scene);
	mainLayout->addWidget(m_view);
	m_pixItem = new QGraphicsPixmapItem();
	scene->addItem(m_pixItem);

	m_colormap = generateStandardQTColorTable(HOT_IRON);
	QColor background(m_colormap[0]);
	m_view->setBackgroundBrush(QBrush(background));

	hide(); // we start hiding
}

void ProgressWidget::setImageData(std::shared_ptr<DoseProgressImageData> data)
{
	if (data) {
		
		const int width = static_cast<int>(data->dimensions[0]);
		const int height = static_cast<int>(data->dimensions[1]);
		
		const double dw = data->spacing[0];
		const double dh = data->spacing[1];

		QImage qim(data->image.data(), width, height, width, QImage::Format_Indexed8);
		qim.setColorTable(m_colormap);
		QTransform transform(dw, .0, .0, -dh, .0, .0); //scale and mirror y axis
		if (height > width)
		{
			QTransform rot;
			rot.rotate(90.0); // flipping image
			transform = transform * rot;
		}
		auto scene = m_view->scene();
		m_pixItem->setPixmap(QPixmap::fromImage(qim));
		m_pixItem->setTransform(transform);
		show(); // we show ourselves
		m_view->fitInView(m_pixItem, Qt::KeepAspectRatio);
	}
	else {
		hide();// hide stuff
	}
}

void ProgressWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	m_view->fitInView(m_pixItem, Qt::KeepAspectRatio);
}