using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Menus {


        public static void imprimeMenu() {
            Console.WriteLine("\t\t\t\tJogador contra Jogador");
            Console.WriteLine("\t\t\t\tJogador contra Computador");
            Console.WriteLine("\t\t\t\tComputador contra Computador");
            Console.WriteLine("\n\n\n\t\t Setas ou WASD e enter para selecionar o modo");
            Console.Write("\n\tControles:");
            Console.WriteLine("\t[[Jogador 1: WASD]]\t[[Jogador 2: Setas]]");
            Console.WriteLine("\t\t\t\t[[Esc para fechar o jogo]]");
        }

        public static void imprimeIntro() {
            Console.WriteLine("\n\t/////////////////\t\tTRON\t\t//////////////////");
            Console.WriteLine("\t/////////////////\tJogo por Thomaz Diniz\t//////////////////\n\n");
        }



    }
}
