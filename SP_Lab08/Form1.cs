using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Diagnostics;

namespace SP_Lab08
{
	public partial class Form1 : Form
	{
		Bitmap hammers;
		Bitmap wywh;
		Graphics pb1Graphics;
		Graphics pb2Graphics;
		Graphics pb3Graphics;
		List<Bitmap> hammersSlices;
		List<Bitmap> wywhSlices;

		Thread hammersThread;
		Stopwatch hammersStopWatch;
		TimeSpan hammersTimeSpan;

		Thread wywhThread;
		Stopwatch wywhStopWatch;
		TimeSpan wywhTimeSpan;

		Thread infoThread;
		Stopwatch infoStopWatch;
		TimeSpan infoTimeSpan;
		string systemInfo;
		Font font = new Font("Arial", 10, FontStyle.Bold);
		public Form1()
		{
			InitializeComponent();
			hammers = new Bitmap("hammers.jpg");
			wywh = new Bitmap("wywh.jpg");
			pb1Graphics = pbImage1.CreateGraphics();
			pb2Graphics = pbImage2.CreateGraphics();
			pb3Graphics = pbImage3.CreateGraphics();
			hammersSlices = SliceImage(hammers);
			wywhSlices = SliceImage(wywh);
			
			hammersStopWatch = new Stopwatch();
			wywhStopWatch = new Stopwatch();
			infoStopWatch = new Stopwatch();

			
		}

		private List<Bitmap> SliceImage(Bitmap img) {
			int fragmentHeight = img.Height / 3;
			int fragmentWidth = img.Width / 3;
			List<Bitmap> imgList = new List<Bitmap> { };
			/*
			 * Нарезка построчно, индексы
			 * 0 1 2
			 * 3 4 5
			 * 6 7 8
			 */
			for (int i = 0; i < fragmentHeight * 3; i += fragmentHeight) {
				for (int j = 0; j < fragmentWidth * 3; j += fragmentWidth) {
					Rectangle rect = new Rectangle(j, i, fragmentWidth, fragmentHeight);
					imgList.Add(img.Clone(rect, img.PixelFormat));
				}
			}
			return imgList;
		}

		// генерация перестановок длины length из элементов list https://stackoverflow.com/a/10630026
		private IEnumerable<IEnumerable<T>> GetPermutations<T>(IEnumerable<T> list, int length)
		{
			if (length == 1) return list.Select(t => new T[] { t });

			return GetPermutations(list, length - 1)
				.SelectMany(t => list.Where(e => !t.Contains(e)),
					(t1, t2) => t1.Concat(new T[] { t2 }));
		}

		// перемешивание полученых перестановок https://stackoverflow.com/a/5807191
		private IEnumerable<T> Shuffle<T>(IEnumerable<T> enumerable)
		{
			var r = new Random();
			return enumerable.OrderBy(x => r.Next()).ToList();
		}

		// возвращает пару (значение, индекс) в коллекции https://thomaslevesque.com/2019/11/18/using-foreach-with-index-in-c/
		private IEnumerable<(T item, int index)> WithIndex<T>(IEnumerable<T> source)
		{
			return source.Select((item, index) => (item, index));
		}

		// отрисовка нарезанной картинки
		private void DrawSliced(Graphics g, List<Bitmap> imgList, List<int> permutation) {
			// для укладывания картинки в размер отсечения
			var clipBounds = g.VisibleClipBounds;
			var visibleWidth = clipBounds.Width / 3;
			var visibleHeight = clipBounds.Height / 3;
			foreach (var (el, idx) in WithIndex(permutation)) {
				g.DrawImage(imgList[el], (idx % 3) * visibleWidth, (idx / 3) * visibleHeight, visibleWidth, visibleHeight);
			}
		}


		private void GoThroughPermutations(Graphics g, List<Bitmap> imgList)
		{
			var trueOrder = Enumerable.Range(0, 9);
			// возвращает список из 9! = 362880 перестановок
			var permutations = GetPermutations(trueOrder, 9);
			permutations = Shuffle(permutations);
			foreach (var (el, idx) in WithIndex(permutations))
			{
				if (idx % 300 == 0) DrawSliced(g, imgList, el.ToList());
				if (el.SequenceEqual(trueOrder))
				{
					DrawSliced(g, imgList, el.ToList());
					break;
				}
			}
		}

		private void hammersImgDoWork() {
			hammersStopWatch.Restart();
			GoThroughPermutations(pb1Graphics, hammersSlices);
			hammersTimeSpan = hammersStopWatch.Elapsed;
		}

		private void wywhImgDoWork() {
			wywhStopWatch.Restart();
			GoThroughPermutations(pb2Graphics, wywhSlices);
			wywhTimeSpan = wywhStopWatch.Elapsed;
		}

		private void infoDoWork() {
			infoStopWatch.Restart();
			systemInfo = GetSystemInfo();
			hammersThread.Join();
			wywhThread.Join();
			pb3Graphics.DrawString(systemInfo, font, Brushes.Olive, pb3Graphics.VisibleClipBounds);
			infoTimeSpan = infoStopWatch.Elapsed;
		}

		private string GetSystemInfo()
		{
			var output = new StringBuilder();
			output.AppendFormat("OSVersion: {0}\n", Environment.OSVersion);
			output.AppendFormat("64 Bit операционная система? : {0}\n",
				Environment.Is64BitOperatingSystem ? "Да" : "Нет");
			output.AppendFormat("Is64BitProcess: {0}\n", Environment.Is64BitProcess);
			output.AppendFormat("Число процессоров: {0}\n", Environment.ProcessorCount);
			output.AppendFormat("Version: {0}\n", Environment.Version.ToString());
			output.AppendFormat("GetFolderPath: {0}\n", Environment.GetFolderPath(Environment.SpecialFolder.System));
			output.AppendFormat("TickCount: {0}\n", Environment.TickCount);
			output.AppendFormat("UserInteractive: {0}\n", Environment.UserInteractive);
			output.AppendFormat("WorkingSet: {0}\n", Environment.WorkingSet);
			output.AppendFormat("Логические диски : {0}\n",
				string.Join(", ", Environment.GetLogicalDrives())
					.Replace("\\", string.Empty));
			return output.ToString();
		}

		private void btnAboutMainThread_Click(object sender, EventArgs e)
		{
			Thread mainThread = Thread.CurrentThread;
			mainThread.Name = "Первичный поток";
			labelAboutMainThread.Text = "Имя домена: " + Thread.GetDomain().FriendlyName +
						//"\nИдентификатор контекста: " + Thread.CurrentContext.ContextID + // нет в .NET Core 3.1 ??
						"\nУровень приоритета: " + mainThread.Priority +
						"\nСостояние потока: " + mainThread.ThreadState.ToString() +
						"\nИмя потока: " + mainThread.Name +
						"\nПоток запущен? " + (mainThread.IsAlive ? "Да" : "Нет");
		}

		private void btnGoSlicing_Click(object sender, EventArgs e)
		{
			hammersThread = new Thread(hammersImgDoWork);
			wywhThread = new Thread(wywhImgDoWork);
			infoThread = new Thread(infoDoWork);

			hammersThread.Start();
			wywhThread.Start();
			infoThread.Start();

			
			infoThread.Join();

			string hammersTimeInfo = String.Format("Первая картинка: {0:00}:{1:000}", hammersTimeSpan.Seconds, hammersTimeSpan.Milliseconds);
			string wywhTimeInfo = String.Format("Вторая картинка: {0:00}:{1:000}", wywhTimeSpan.Seconds, wywhTimeSpan.Milliseconds);
			string infoTimeInfo = String.Format("Информация о системе: {0:00}:{1:000}", infoTimeSpan.Seconds, infoTimeSpan.Milliseconds);
			labelAboutMainThread.Text = "Время выполнения:" + "\n" + hammersTimeInfo + "\n" + wywhTimeInfo + "\n" + infoTimeInfo;
			
			
		}

	}
}
