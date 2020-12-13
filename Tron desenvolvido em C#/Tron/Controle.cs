using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Controle {
        public static bool PressW = false;
        public static bool PressA = false;
        public static bool PressS = false;
        public static bool PressD = false;

        public static bool PressESQ = false;
        public static bool PressDIR = false;
        public static bool PressCIM = false;
        public static bool PressBAI = false;

        public static bool PressESC = false;
        public static bool PressENTER = false;


        public static void atualiza() {
            PressW = false;
            PressA = false;
            PressS = false;
            PressD = false;

            PressESQ = false;
            PressDIR = false;
            PressCIM = false;
            PressBAI = false;

            PressESC = false;
            PressENTER = false;

    
            if (Console.KeyAvailable) {
                switch ( Console.ReadKey(true).Key ) {
                    case ConsoleKey.W: PressW = true; break;
                    case ConsoleKey.A: PressA = true; break;
                    case ConsoleKey.S: PressS = true; break;
                    case ConsoleKey.D: PressD = true; break;

                    case ConsoleKey.LeftArrow:  PressESQ = true; break;
                    case ConsoleKey.RightArrow: PressDIR = true; break;
                    case ConsoleKey.UpArrow:    PressCIM = true; break;
                    case ConsoleKey.DownArrow:  PressBAI = true; break;

                    case ConsoleKey.Enter:  PressENTER = true;  break;
                    case ConsoleKey.Escape: PressESC = true;    break;
                }
            }
            
        }

    }
}
