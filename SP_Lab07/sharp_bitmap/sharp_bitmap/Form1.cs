using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace sharp_bitmap
{
	public partial class Form1 : Form
	{
		Font font = new Font("Arial", 20, FontStyle.Bold); // шрифт для надписи
		// имена файлов с картинками
		List<string> bitmapsNames = new List<string>{ "FL.png", "genTestSet.png", "spectrogram.png", "mcm2.png"};
		// надписи, соответствующие картинкам
		List<string> names = new List<string> {"Цветок (график)", "Сгенерированные цифры", "Спектрограмма", "Матрица ошибок"};
		// список для картинок
		List<Bitmap> bitmaps = new List<Bitmap> { };
		int currentBitmap = 0;
		bool zoomed = false; // флаг состояния, когда приближена картинка
		bool isZooming = false; // флаг состояния, когда картинка приближается (отдаляется)
		int currentZoom = 0; // текущее значение приближения
		int zoomDirection = -1; // направление [приближение / отдаление]
		RectangleF textRect; // прямоугольник для текста
		public Form1()
		{
			InitializeComponent();
			// добавляем картинки в список
			foreach (string el in bitmapsNames) {
				bitmaps.Add(new Bitmap("../../../" + el));
			}
			textRect = pictureBox1.ClientRectangle;
			textRect.Height = 50;
			textRect.X += textRect.Width / 2;
			textRect.Y += 20;

		}

		private void btnPrev_Click(object sender, EventArgs e)
		{
			// уменьшаем индекс текущей картинки (с закольцовыванием)
			if (currentBitmap <= 0) currentBitmap = bitmaps.Count - 1;
			else currentBitmap--;
			zoomed = false;
			Refresh(); // для обновления надписи
		}

		private void btnZoom_Click(object sender, EventArgs e)
		{
			isZooming = true;
			zoomDirection *= -1;
			if (zoomed) currentZoom = 200;
			else currentZoom = 0;
			pictureBox1.Invalidate();
		}

		private void pictureBox1_Paint(object sender, PaintEventArgs e)
		{
			pictureBox1.Invalidate(); // будем перерисовывать область pictureBox1
			if (isZooming)
			{
				// обработка текущего приближения (выход за пределы приближения)
				if (currentZoom > 200 || currentZoom < 0) {
					isZooming = false;
					zoomed = !zoomed;
				}
				
				currentZoom += zoomDirection * 5;
				e.Graphics.DrawImage(bitmaps[currentBitmap], 0 - currentZoom, 0 - currentZoom, pictureBox1.Width + 2 * currentZoom, pictureBox1.Height + 2 * currentZoom);

			}
			else {
				// обработка состояний, когда приближена картинка и нет
				if (zoomed)  e.Graphics.DrawImage(bitmaps[currentBitmap], -200, -200, pictureBox1.Width + 400, pictureBox1.Height + 400);
				else e.Graphics.DrawImage(bitmaps[currentBitmap], 0, 0, pictureBox1.Width, pictureBox1.Height);
			}
			
		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			// на форме рисуем текст
			e.Graphics.DrawString(names[currentBitmap], font, Brushes.Olive, textRect);
		}

		private void btnNext_Click(object sender, EventArgs e)
		{
			// увеличиваем индекс текущей картинки (с закольцовыванием)
			if (currentBitmap >= bitmaps.Count - 1) currentBitmap = 0;
			else currentBitmap++;
			zoomed = false;
			Refresh(); // для обновления надписи
		}
	}
}
