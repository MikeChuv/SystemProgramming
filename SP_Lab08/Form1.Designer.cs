
namespace SP_Lab08
{
    partial class Form1
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
            this.btnAboutMainThread = new System.Windows.Forms.Button();
            this.labelAboutMainThread = new System.Windows.Forms.Label();
            this.pbImage1 = new System.Windows.Forms.PictureBox();
            this.pbImage2 = new System.Windows.Forms.PictureBox();
            this.btnGoSlicing = new System.Windows.Forms.Button();
            this.pbImage3 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage3)).BeginInit();
            this.SuspendLayout();
            // 
            // btnAboutMainThread
            // 
            this.btnAboutMainThread.Location = new System.Drawing.Point(674, 14);
            this.btnAboutMainThread.Margin = new System.Windows.Forms.Padding(5);
            this.btnAboutMainThread.Name = "btnAboutMainThread";
            this.btnAboutMainThread.Size = new System.Drawing.Size(363, 38);
            this.btnAboutMainThread.TabIndex = 0;
            this.btnAboutMainThread.Text = "О главном потоке";
            this.btnAboutMainThread.UseVisualStyleBackColor = true;
            this.btnAboutMainThread.Click += new System.EventHandler(this.btnAboutMainThread_Click);
            // 
            // labelAboutMainThread
            // 
            this.labelAboutMainThread.AutoEllipsis = true;
            this.labelAboutMainThread.BackColor = System.Drawing.SystemColors.ControlLight;
            this.labelAboutMainThread.Font = new System.Drawing.Font("Segoe UI", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.labelAboutMainThread.Location = new System.Drawing.Point(674, 70);
            this.labelAboutMainThread.Name = "labelAboutMainThread";
            this.labelAboutMainThread.Size = new System.Drawing.Size(363, 200);
            this.labelAboutMainThread.TabIndex = 1;
            this.labelAboutMainThread.Text = "Для информации";
            // 
            // pbImage1
            // 
            this.pbImage1.Location = new System.Drawing.Point(24, 12);
            this.pbImage1.Name = "pbImage1";
            this.pbImage1.Size = new System.Drawing.Size(286, 258);
            this.pbImage1.TabIndex = 2;
            this.pbImage1.TabStop = false;
            // 
            // pbImage2
            // 
            this.pbImage2.Location = new System.Drawing.Point(316, 13);
            this.pbImage2.Name = "pbImage2";
            this.pbImage2.Size = new System.Drawing.Size(293, 257);
            this.pbImage2.TabIndex = 3;
            this.pbImage2.TabStop = false;
            // 
            // btnGoSlicing
            // 
            this.btnGoSlicing.Location = new System.Drawing.Point(24, 276);
            this.btnGoSlicing.Name = "btnGoSlicing";
            this.btnGoSlicing.Size = new System.Drawing.Size(197, 41);
            this.btnGoSlicing.TabIndex = 4;
            this.btnGoSlicing.Text = "Нарезать";
            this.btnGoSlicing.UseVisualStyleBackColor = true;
            this.btnGoSlicing.Click += new System.EventHandler(this.btnGoSlicing_Click);
            // 
            // pbImage3
            // 
            this.pbImage3.BackColor = System.Drawing.SystemColors.ControlLight;
            this.pbImage3.Location = new System.Drawing.Point(250, 293);
            this.pbImage3.Name = "pbImage3";
            this.pbImage3.Size = new System.Drawing.Size(786, 259);
            this.pbImage3.TabIndex = 5;
            this.pbImage3.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1063, 579);
            this.Controls.Add(this.pbImage3);
            this.Controls.Add(this.btnGoSlicing);
            this.Controls.Add(this.pbImage2);
            this.Controls.Add(this.pbImage1);
            this.Controls.Add(this.labelAboutMainThread);
            this.Controls.Add(this.btnAboutMainThread);
            this.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pbImage1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnAboutMainThread;
        private System.Windows.Forms.Label labelAboutMainThread;
        private System.Windows.Forms.PictureBox pbImage1;
        private System.Windows.Forms.PictureBox pbImage2;
        private System.Windows.Forms.Button btnGoSlicing;
        private System.Windows.Forms.PictureBox pbImage3;
    }
}

