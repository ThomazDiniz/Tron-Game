using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Program {
        enum Estados {
            DesenhaIntro, Menu, CarregaSala, Jogo, TelaVencedor
        };
        
        static void Main(string[] args) {
            Estados Estado = Estados.DesenhaIntro;

            Player jogador1 = new Player();
            Player jogador2 = new Player();

            bool computador1 = false;
            bool computador2 = false;

            int vencedor = 0;
            int botaoMenu = 0;
            int empate = 0;

            while (true) {
                Controle.atualiza();
                if (Controle.PressESC) { break; }

                switch (Estado) {
                    case Estados.DesenhaIntro:
                        Console.Clear();
                        botaoMenu = 0;
                        Menus.imprimeIntro();
                        Menus.imprimeMenu();
                        Console.SetCursorPosition(31, 5+botaoMenu);
                        Console.Write(">");
                        Console.SetCursorPosition(31, 5+botaoMenu);
                        Estado++;
                    break;
                        //30,5
                    case Estados.Menu:
                        if (Controle.PressW || Controle.PressS || Controle.PressCIM || Controle.PressBAI) {

                            Console.SetCursorPosition(31, 5 + botaoMenu);
                            Console.Write(" ");

                            if ((Controle.PressCIM) || (Controle.PressW))
                                botaoMenu--;
                            if ((Controle.PressBAI) || (Controle.PressS))
                                botaoMenu++;
                            if (botaoMenu > 2)
                                botaoMenu = 0;
                            if (botaoMenu < 0)
                                botaoMenu = 2;
                            Console.SetCursorPosition(31, 5 + botaoMenu);
                            Console.Write(">");
                        }

                        if (Controle.PressENTER) {
                            Estado++;
                            Console.Clear();
                        }
                    break;

                    case Estados.CarregaSala:
                        //Zera Jogadores;
                        jogador1.setPosicao(-5 + Tabuleiro.TW / 4, Tabuleiro.TH / 2);
                        jogador1.setVelocidade(1, 0);
         
                        jogador2.setPosicao(6 + 3*Tabuleiro.TW / 4, Tabuleiro.TH / 2);
                        jogador2.setVelocidade(-1, 0);
                        

                        //Determina quem vai ser IA e quem não vai ser IA;
                        if (botaoMenu == 0) {
                            computador1 = false;
                            computador2 = false;
                        } else if (botaoMenu == 1) {
                            computador1 = false;
                            computador2 = true;
                        } else {
                            computador1 = true;
                            computador2 = true;
                        }

                        Menus.imprimeIntro();
                        System.Threading.Thread.Sleep(1000);
                        //Zera Tabuleiro
                        Tabuleiro.zeraSala();
                        Estado++;

                    break;

                    case Estados.Jogo:
                        if (computador1) {
                            Controlador.controla(jogador1);
                        } else {
                            if (Controle.PressA) { jogador1.setVX(-1); }
                            if (Controle.PressD) { jogador1.setVX(1); }
                            if (Controle.PressW) { jogador1.setVY(-1); }
                            if (Controle.PressS) { jogador1.setVY(1); }
                        }

                        if (computador2) {
                            Controlador.controla(jogador2);
                        } else {
                            if (Controle.PressESQ) { jogador2.setVX(-1); }
                            if (Controle.PressDIR) { jogador2.setVX(1); }
                            if (Controle.PressCIM) { jogador2.setVY(-1); }
                            if (Controle.PressBAI) { jogador2.setVY(1); }
                        }

                        jogador1.atualiza();
                        jogador2.atualiza();

                        jogador1.desenha();
                        jogador2.desenha();

                        empate = 0;
                        vencedor = 0;

                        if (jogador1.morreu()) {vencedor = 2; jogador1.jogadorDesenhaMorte(); empate++; }
                        if (jogador2.morreu()) {vencedor = 1; jogador2.jogadorDesenhaMorte(); empate++; }

                        if (empate == 2)
                            vencedor = 3;
                        if (vencedor != 0)
                            Estado++;

                        jogador1.marca();
                        jogador2.marca();

                        System.Threading.Thread.Sleep(100);
                        break;

                    case Estados.TelaVencedor:
                        System.Threading.Thread.Sleep(500);
                        Console.Clear();
                        Console.SetCursorPosition(Tabuleiro.TX + Tabuleiro.TW / 3, Tabuleiro.TY + Tabuleiro.TH / 3);
                        if (vencedor == 3) {
                            Console.Write("O jogo empatou :(");
                        } else {
                            Console.Write("Jogador {0} Venceu! :D", vencedor);
                        }
                        System.Threading.Thread.Sleep(2000);

                        Estado = 0;
                        break;

                }
                
                
            }
        }


    }
}
