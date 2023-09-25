using WindowsInput;
using System.Runtime.InteropServices;



    namespace COLORAIMBOT
{
    public partial class ColorAimbot : Form
    {
        [DllImport("user32.dll")]
        private static extern short GetAsyncKeyState(Keys vKey);
        private InputSimulator inputSimulator = new InputSimulator();
        private Keys aimbotHotkey = Keys.XButton2;
        public ColorAimbot()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label1.Text = "Aimbot hotkey -> " + aimbotHotkey .ToString() +"<-";
            Thread logicThread = new Thread(Mainlogic) { IsBackground = true };
            logicThread.Start();

        }
        private void Mainlogic()

        {
            while (true)
            {
                if (IsHotKeyPressed(aimbotHotkey))
                {
                    var foundColorPosition = FindColorPosition(ConvertIntColor(0xD885FF), 911, 535, 1028, 680);
                    if (!foundColorPosition.IsEmpty)
                    {
                        inputSimulator.Mouse.MoveMouseBy(foundColorPosition.X - 960, foundColorPosition.Y - 540);
                        Thread.Sleep(100);
                    }
                    var foundColorPosition1 = FindColorPosition(ConvertIntColor(0xD885FF), 911, 535, 1028, 680);
                    if (!foundColorPosition.IsEmpty)
                    {
                        inputSimulator.Mouse.MoveMouseBy(foundColorPosition.X - 960, foundColorPosition.Y - 540);
                        Thread.Sleep(100);
                    }


                }
            }
        
        }

        private Color ConvertIntColor(int intColor)
        { 
          int red = (intColor >> 16) & 0xff;
            int green = (intColor >> 8) & 0xff;
            int blue = (intColor >> 0) & 0xff;
            return Color.FromArgb(red, green, blue);
        
        }

        private Point FindColorPosition(Color targetColor, int startX, int startY, int endX, int endY)
        {
            using (Bitmap screenshot = new Bitmap(endX - startX, endY - startY))
            using (Graphics g = Graphics.FromImage(screenshot))
            {
                g.CopyFromScreen(new Point(startX, startY), Point.Empty,screenshot.Size);

                for (int x = 0; x < screenshot.Width; x++)
                {
                    for (int y = 0; y < screenshot.Height; y++)
                    {
                        Color pixelColor = screenshot.GetPixel(x, y);
                        if (AreColorsSimilar(targetColor, pixelColor, 30))

                        {
                            return new Point(x + startX, y + startY);

                        }
                    }
                }
                return Point.Empty;
            }

        }
        private bool AreColorsSimilar(Color color1, Color color2, int maxColorDifference)
        {
            int redDifference = Math.Abs(color1.R - color2.R);
            int greenDifference = Math.Abs(color1.G - color2.G);
            int blueDifference = Math.Abs(color1.G - color2.G);
            return redDifference <= maxColorDifference && redDifference >= maxColorDifference && greenDifference <= maxColorDifference;

        }
        private bool IsHotKeyPressed(Keys vKey)
        {
            return GetAsyncKeyState(vKey) < 0;
        }

    }
}
