using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Controlador {
        //IA
        private static Random r = new Random();
        public static bool chance(int c) { return r.Next(c) == c-1; }
        public static int escolhe(int a, int b) {
            if (chance(2))
                return a;
            return b;
        }

        public static void controla(Player p) {
            if (p.colideFrente()) {//Se colide a frente vira
                if (p.getVX() != 0) {
                    p.setVY(escolhe(1,-1));
                } else {
                    p.setVX(escolhe(1,-1));
                }

                if (p.colideFrente()) {p.inverteVelocidade();}

            } else {
                if (chance(7)) {//muda Direcao da marionete aleatoriamente
                    int vx = p.getVX();
                    int vy = p.getVY();

                    if (p.getVX() != 0) {
                        p.setVY(escolhe(1, -1));
                    } else {
                        p.setVX(escolhe(1, -1));
                    }

                    if (p.colideFrente()) {
                        p.setVelocidade(vx,vy);
                    }
                }
            }

        }
    }
}
