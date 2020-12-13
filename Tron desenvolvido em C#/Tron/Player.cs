using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Player {
        private Vetor posicao;
        private Vetor velocidade;
        public Player() {
            posicao = new Vetor();
            velocidade = new Vetor();
        }
        public Player(Vetor posicao, Vetor velocidade) {
            this.posicao = posicao;
            this.velocidade = velocidade;
        }
        public Player(int x, int y, int vx, int vy) {
            this.posicao = new Vetor(x,y);
            this.velocidade = new Vetor(vx,vy);
        }

        public Vetor getPosicao() { return posicao; }
        public Vetor getVelocidade() { return velocidade; }
        public void setPosicao(Vetor posicao) { this.posicao = posicao; }
        public void setVelocidade(Vetor velocidade) { this.velocidade = velocidade; }
        public void setPosicao(int x, int y) { this.posicao = new Vetor(x,y); }
        public int getVX() { return velocidade.x; }
        public int getVY() { return velocidade.y; }

        public void inverteVelocidade() { velocidade *= new Vetor(-1,-1); }

        public void setVelocidade(int x, int y) { 
            this.velocidade = new Vetor(x, y);
        }

        public void setVX(int vx) {
            if (this.velocidade.x == 0) {
                this.velocidade.x = vx;
                this.velocidade.y = 0;
            }
        }

        public void setVY(int vy) {
            if (this.velocidade.y == 0) {
                this.velocidade.y = vy;
                this.velocidade.x = 0;
            }
        }

        public void atualiza() {
            posicao += velocidade;
            if (this.posicao.x < 0)     { this.posicao.x = 0; }
            if (this.posicao.x > Tabuleiro.TW-1)    { this.posicao.x = Tabuleiro.TW - 1; }
            if (this.posicao.y < 0)     { this.posicao.y = 0; }
            if (this.posicao.y > Tabuleiro.TH - 1)    { this.posicao.y = Tabuleiro.TH - 1; }
        }

        public void desenha() { Console.SetCursorPosition(Tabuleiro.TX+posicao.x,Tabuleiro.TY+posicao.y); Console.Write("O"); }

        public void marca() {
            Tabuleiro.marca(posicao);
        }

        public bool morreu() {
            return !Tabuleiro.sala[posicao.x,posicao.y];
        }

        public bool colideFrente() {
            Vetor p = posicao + velocidade;
            return !Tabuleiro.sala[p.x, p.y];
        }

        public void jogadorDesenhaMorte() {
            System.Threading.Thread.Sleep(300);
            char c = '#';
            for (int k = 0; k < 6; k++) {
                for (int m = 0; m < 2; m++) {
                    for (int i = -k * 2; i < k * 2; i++) {
                        for (int j = -k; j < k; j++) {
                            Console.SetCursorPosition(Tabuleiro.TX+posicao.x+i, Tabuleiro.TY+posicao.y+j);
                            Console.Write(c);//Desenha
                        }
                    }
                    System.Threading.Thread.Sleep(100);
                    if (c == '#') { c = 'X'; } else if (c == 'X') { c = '%'; } else { c = '#'; }
                }

            }


        }

    }
}
