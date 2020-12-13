using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tron {
    class Vetor {
        public int x;
        public int y;

        public Vetor(int x, int y) {
            this.x = x;
            this.y = y;
        }
        public Vetor() {
            this.x = 0;
            this.y = 0;
        }

        public static Vetor operator+(Vetor v1, Vetor v2){
            return new Vetor(v1.x + v2.x, v1.y + v2.y);    
        }

        public static Vetor operator*(Vetor v1, Vetor v2) {
            return new Vetor( v1.x*v2.x, v1.y*v2.y );
        }


    }
}
