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

namespace SP_Lab06
{
    public partial class MainForm : Form
    {
        bool emblemFlag, olympicFlag, gameFlag;
        static Image emblem;
        static Game game;
        public MainForm()
        {
            InitializeComponent();
            emblemFlag = olympicFlag = gameFlag = false;
            emblem = Image.FromFile("playbtn.png");
            boardSizeUD.Value = 4;
        }

        public void labelShow(string message) {
            labelGame.Text = message;
        }

        private void btnEmblem_Click(object sender, EventArgs e)
        {
            emblemFlag = !emblemFlag;
            olympicFlag = gameFlag = false;
            Refresh(); // чтобы вызвалсь Paint кнопок
        }
        private void btnOlympic_Click(object sender, EventArgs e)
        {
            olympicFlag = !olympicFlag;
            emblemFlag = gameFlag = false;
            Refresh(); // чтобы нарисовать в picturebox и убрать эмблему с кнопок
        }
        private void btnGame_Click(object sender, EventArgs e)
        {
            gameFlag = !gameFlag;
            emblemFlag = olympicFlag = false;
            int bSize = (int)boardSizeUD.Value;
            if (bSize < 4)
            {
                bSize = 4;
                boardSizeUD.Value = 4;
            }
            else if (bSize > 10)
            {
                bSize = 10;
                boardSizeUD.Value = 10;
            }
            Refresh(); // очищаем от предыдущих действий
            if (gameFlag) {
                game = new Game(bSize, pictureBox1);
                game.main = this; // для пересылки информации о состоянии игры
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (gameFlag) game.BoardClicked(e.X, e.Y);
        }

        private void btnEmblem_Paint(object sender, PaintEventArgs e)
        {
            if (emblemFlag) e.Graphics.DrawImage(emblem, 10, 10, 40, 40);
        }

        private void btnOlympic_Paint(object sender, PaintEventArgs e)
        {
            if (emblemFlag) e.Graphics.DrawImage(emblem, 10, 10, 40, 40);
        }

        private void btnGame_Paint(object sender, PaintEventArgs e)
        {
            if (emblemFlag) e.Graphics.DrawImage(emblem, 10, 10, 40, 40);
        }

        private void btnSetBoardSize_Click(object sender, EventArgs e)
        {
            if (gameFlag)
            {
                int bSize = (int)boardSizeUD.Value;
                if (bSize < 4)
                {
                    bSize = 4;
                    boardSizeUD.Value = 4;
                }
                else if (bSize > 10) {
                    bSize = 10;
                    boardSizeUD.Value = 10;
                }

                Refresh();
                game = new Game(bSize, pictureBox1);
                game.main = this; // для пересылки информации о состоянии игры
            }
        }


        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (olympicFlag)
            {

                int radius = 50;
                int shift = 10;
                int penSize = 10;

                Pen pen = new Pen(Color.FromArgb(0, 133, 199), penSize);
                Rectangle rect = new Rectangle(radius, radius, radius * 2, radius * 2);
                e.Graphics.DrawEllipse(pen, rect);

                pen.Color = Color.FromArgb(244, 195, 0);
                rect.X += radius + shift;
                rect.Y = radius * (1 + 3 / 2);
                e.Graphics.DrawEllipse(pen, rect);

                pen.Color = Color.Black;
                rect.X += radius + shift;
                rect.Y = radius;
                e.Graphics.DrawEllipse(pen, rect);

                pen.Color = Color.FromArgb(0, 159, 61);
                rect.X += radius + shift;
                rect.Y = radius * (1 + 3 / 2);
                e.Graphics.DrawEllipse(pen, rect);

                pen.Color = Color.Red;
                rect.X += radius + shift;
                rect.Y = radius;
                e.Graphics.DrawEllipse(pen, rect);

                // Зарисовка наложений колец
                pen.Color = Color.FromArgb(0, 133, 199);
                rect.X = radius;
                rect.Y = radius;
                e.Graphics.DrawArc(pen, rect, 340, 40);

                pen.Color = Color.FromArgb(244, 195, 0);
                rect.X += radius + shift;
                rect.Y = radius * (1 + 3 / 2);
                e.Graphics.DrawArc(pen, rect, 270, 40);

                pen.Color = Color.Black;
                rect.X += radius + shift;
                rect.Y = radius;
                e.Graphics.DrawArc(pen, rect, 340, 40);

                pen.Color = Color.FromArgb(0, 159, 61);
                rect.X += radius + shift;
                rect.Y = radius * (1 + 3 / 2);
                e.Graphics.DrawArc(pen, rect, 270, 40);

            }
        }

        
    }


    public class Game
    {
        // данные игры

        // состояния - Игра продолжается, Первый игрок выиграл, Второй игрок выиграл
        enum State { Playing, Win1, Win2} 
        State _currentState; // текущее состояние игры
        public MainForm main;
        int _currentPlayer;
        int[,] _board; // матрица с ходами
        int _boardSize; // размер поля (кол-во клеток)
        Rectangle _boardRect; // прямоугольник поля
        int _xSize, _ySize; // размеры клетки поля
        Graphics _g; // для рисования на поверхности поля

        public Game(int boardSize, PictureBox pbox) {
            _g = Graphics.FromHwnd(pbox.Handle);
            _boardSize = boardSize;
            _boardRect = pbox.ClientRectangle;
            _xSize = _boardRect.Width / _boardSize;
            _ySize = _boardRect.Height / _boardSize;
            _currentPlayer = 1;
            _board = new int[_boardSize, _boardSize];
            Array.Clear(_board, 0, _board.Length);
            _currentState = State.Playing;
            PaintBg();
        }

        // рисование фона игрового поля и сетки
        private void PaintBg()
        {
            Bitmap image1 = (Bitmap)Image.FromFile("wood.jpg", true);
            TextureBrush texture = new TextureBrush(image1);
            _g.FillRectangle(texture, _boardRect); // фон - текстурная кисть
            Pen pen = new Pen(Color.Black, 3);
            for (int i = 0; i < _boardSize; i++)
            {
                _g.DrawLine(pen, _xSize * i + i, 0, _xSize * i + i, _boardRect.Width - 1);
                _g.DrawLine(pen, 0, _ySize * i + i, _boardRect.Height - 1, _ySize * i + i);
            }
        }

        // определение победителя: кто первый соберет 4 клетки в столбце или строке
        private int CheckWinner(string key) {
            for (int j = 0; j < _board.GetLength(key == "row" ? 1 : 0); ++j) {
                int pred = key == "row" ? _board[0, j] : _board[j, 0]; // выбор начальной клетки
                int curPlayer = pred;
                int counter = 0;
                for (int i = 1; i < _board.GetLength(key == "col" ? 1 : 0); ++i) {
                    int cur = key == "row" ? _board[i, j] : _board[j, i];
                    if (pred == cur && pred != 0) // ряд/столбец продолжается
                    {
                        counter++;
                    }
                    else // ряд/столбец прерван
                    {
                        counter = 0;
                        curPlayer = cur;
                    }
                    pred = cur;
                    if (counter == 3) return curPlayer;
                }
            }
            return 0;
        }

        // кликнули по полю в точку {x, y}
        public void BoardClicked(int x, int y) {

            // определяем клетку, в которой кликнули
            int xCell = x / _xSize;
            int yCell = y / _ySize;
            
            // рисование фигуры, соответствующей игроку и изменение матрицы совершенных ходов
            Rectangle markerRect = new Rectangle(xCell * (_xSize + 1) + _xSize / 4, yCell * (_ySize + 1) + _ySize / 4, _xSize / 2, _ySize / 2);
            if (_currentPlayer == 1) { // ход совершает первый игрок
                if (_board[xCell, yCell] == 0 && _currentState == State.Playing) {
                    LinearGradientBrush linGrBrush = new LinearGradientBrush(
                       markerRect,
                       Color.Red,
                       Color.Blue,
                       90);
                    _g.FillRectangle(linGrBrush, markerRect);
                    _board[xCell, yCell] = _currentPlayer; // пишем в ячейку матрицы номер игрока
                    _currentPlayer = 2; // переход ко второму игроку
                    main.labelShow("Ходит второй");
                }
                else main.labelShow("Занято");
            }
            else if (_currentPlayer == 2) { // ход совершает второй игрок
                if (_board[xCell, yCell] == 0 && _currentState == State.Playing) {
                    int penSize = _xSize / 5;
                    Pen pen = new Pen(Color.FromArgb(200, 100, 0, 0), penSize);
                    HatchBrush brush = new HatchBrush(
                        HatchStyle.DashedHorizontal,
                        Color.Red,
                        Color.FromArgb(255, 200, 200, 0));
                    _g.DrawEllipse(pen, markerRect);
                    _g.FillEllipse(brush, markerRect);
                    _board[xCell, yCell] = _currentPlayer; // пишем в ячейку матрицы номер игрока
                    _currentPlayer = 1; // переход к первому игроку
                    main.labelShow("Ходит первый");
                }
                else main.labelShow("Занято");
            }

            // определение победителя
            int winnerRows = CheckWinner("row");
            int winnerColls = CheckWinner("col");
            int winner = winnerRows == 0 ? winnerColls : winnerRows;
            switch (winner) {
                case 1:
                    {
                        main.labelShow("Первый выиграл");
                        _currentState = State.Win1;
                        break;
                    }
                case 2:
                    {
                        main.labelShow("Второй выиграл");
                        _currentState = State.Win2;
                        break;
                    }
            }

        }

        
    }
}
