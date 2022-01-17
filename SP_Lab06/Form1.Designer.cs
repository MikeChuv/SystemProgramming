
namespace SP_Lab06
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnEmblem = new System.Windows.Forms.Button();
            this.btnOlympic = new System.Windows.Forms.Button();
            this.btnGame = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.boardSizeUD = new System.Windows.Forms.NumericUpDown();
            this.labelGame = new System.Windows.Forms.Label();
            this.btnSetBoardSize = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.boardSizeUD)).BeginInit();
            this.SuspendLayout();
            // 
            // btnEmblem
            // 
            this.btnEmblem.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnEmblem.Location = new System.Drawing.Point(79, 434);
            this.btnEmblem.Margin = new System.Windows.Forms.Padding(5);
            this.btnEmblem.Name = "btnEmblem";
            this.btnEmblem.Size = new System.Drawing.Size(189, 64);
            this.btnEmblem.TabIndex = 0;
            this.btnEmblem.Text = "Эмблема";
            this.btnEmblem.UseVisualStyleBackColor = true;
            this.btnEmblem.Click += new System.EventHandler(this.btnEmblem_Click);
            this.btnEmblem.Paint += new System.Windows.Forms.PaintEventHandler(this.btnEmblem_Paint);
            // 
            // btnOlympic
            // 
            this.btnOlympic.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnOlympic.Location = new System.Drawing.Point(311, 434);
            this.btnOlympic.Name = "btnOlympic";
            this.btnOlympic.Size = new System.Drawing.Size(164, 64);
            this.btnOlympic.TabIndex = 1;
            this.btnOlympic.Text = "Флаг";
            this.btnOlympic.UseVisualStyleBackColor = true;
            this.btnOlympic.Click += new System.EventHandler(this.btnOlympic_Click);
            this.btnOlympic.Paint += new System.Windows.Forms.PaintEventHandler(this.btnOlympic_Paint);
            // 
            // btnGame
            // 
            this.btnGame.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnGame.Location = new System.Drawing.Point(508, 434);
            this.btnGame.Name = "btnGame";
            this.btnGame.Size = new System.Drawing.Size(168, 64);
            this.btnGame.TabIndex = 2;
            this.btnGame.Text = "Игра";
            this.btnGame.UseVisualStyleBackColor = true;
            this.btnGame.Click += new System.EventHandler(this.btnGame_Click);
            this.btnGame.Paint += new System.Windows.Forms.PaintEventHandler(this.btnGame_Paint);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(76, 26);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(400, 400);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            // 
            // boardSizeUD
            // 
            this.boardSizeUD.Location = new System.Drawing.Point(540, 26);
            this.boardSizeUD.Name = "boardSizeUD";
            this.boardSizeUD.Size = new System.Drawing.Size(120, 32);
            this.boardSizeUD.TabIndex = 4;
            // 
            // labelGame
            // 
            this.labelGame.AutoSize = true;
            this.labelGame.Location = new System.Drawing.Point(527, 200);
            this.labelGame.Name = "labelGame";
            this.labelGame.Size = new System.Drawing.Size(0, 25);
            this.labelGame.TabIndex = 5;
            // 
            // btnSetBoardSize
            // 
            this.btnSetBoardSize.Location = new System.Drawing.Point(540, 78);
            this.btnSetBoardSize.Name = "btnSetBoardSize";
            this.btnSetBoardSize.Size = new System.Drawing.Size(119, 32);
            this.btnSetBoardSize.TabIndex = 6;
            this.btnSetBoardSize.Text = "Установить";
            this.btnSetBoardSize.UseVisualStyleBackColor = true;
            this.btnSetBoardSize.Click += new System.EventHandler(this.btnSetBoardSize_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(737, 547);
            this.Controls.Add(this.btnSetBoardSize);
            this.Controls.Add(this.labelGame);
            this.Controls.Add(this.boardSizeUD);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.btnGame);
            this.Controls.Add(this.btnOlympic);
            this.Controls.Add(this.btnEmblem);
            this.Font = new System.Drawing.Font("Segoe UI", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "MainForm";
            this.Text = "Лабораторная работа №6";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.boardSizeUD)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnEmblem;
        private System.Windows.Forms.Button btnOlympic;
        private System.Windows.Forms.Button btnGame;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.NumericUpDown boardSizeUD;
        private System.Windows.Forms.Button btnSetBoardSize;
        private System.Windows.Forms.Label labelGame;
    }
}

