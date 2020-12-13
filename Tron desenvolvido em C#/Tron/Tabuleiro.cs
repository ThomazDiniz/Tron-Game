using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Tabuleiro {
        public static int TW = 60;
        public static int TH = 20;
        public static int TX = 10;
        public static int TY = 5;


        public static bool[,] sala = new bool[60,20];

        public static void zeraSala() {
            for (int i = 0; i < 60; i++) {
                for (int j = 0; j < 20; j++) {
                    sala[i, j] = true;

                    if (i == 0)
                        sala[i,j] = false;
                    if (i == TW - 1)
                        sala[i,j] = false;
                    if (j == 0)
                        sala[i,j] = false;
                    if (j == TH - 1)
                        sala[i,j] = false;
                    if (!sala[i, j]) {
                        Console.SetCursorPosition(TX+i, TY+j);
                        Console.Write("#");
                        System.Threading.Thread.Sleep(10);
                    }

                }
            }
        }

        public static void marca(int x, int y) {
            sala[x, y] = false;
        }
        public static void marca(Vetor p) {
            sala[p.x, p.y] = false;
        }


    }
}
