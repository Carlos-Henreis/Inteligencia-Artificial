
public class MLP {

    double[] entradas;//saida do Entradas
    double[] escondida;//saida do neoronio oculto
    double saida;//neoronio de saida
    double[][] wEntEsc;//Peso da camada entrada para a oculta
    double[] wEscSaida;//Pesos da camada escondida para a camada de saída  
    int qtdtreino;
    double aprendizado = 0.06;
    double [][] amostras = {
                            {0,0}, 
                            {1,0}, 
                            {0,1}, 
                            {1,1}//amostras para o treinamento
                           };
    double [] saidas = {0,1,1,0};   //saidas desejadas

    public MLP(){//Multilayer perceptron
        entradas = new double[amostras[0].length];//Tem o tamanho das qtd das entradas
        escondida = new double[2];//possui tre neoronios
        wEntEsc = new double[entradas.length][escondida.length];//matriz que contem os pesos
        wEscSaida = new double[escondida.length];//Vetor com os pesos
        
        IniciaPeso();//Inicia os pessos
    }

    public  void IniciaPeso(){
        //inicia os pesos da camada entrada/oculta
        for(int i = 0; i < entradas.length; i++){
            for (int j = 0; j < wEntEsc[i].length; j++){       
                wEntEsc[i][j] = Math.random() * 0.2 + 0.1;//valores aleatórios de 0<x<1
            }
        }
        //Inicia pesos entre a camada oculta/saida
        for (int i = 0; i < wEscSaida.length; i++){
            wEscSaida[i] = Math.random() * 0.2 + 0.1;//valores aleatórios de 0<x<1
        }
    }

    public void forward(){//cálculo da saida
        double saidanova;
        //calculo das saidas dos perceptrons da camada intermediária 
        for (int i = 0; i < escondida.length; i++){
            saidanova = 0;             
            for (int j = 0; j < entradas.length; j++){
                saidanova += entradas[j] * wEntEsc[j][i];//soma a entrada com a ponderação dos pesos
            }
            escondida[i] = saidanova;
            //trata a saida para aumentar a eficiencia do treinamento
            if (escondida[i] > 0.5)
                escondida[i] = 1;
            else 
                escondida[i] = 0;
        }
        //trata a última camada
        saida = 0;
        for (int i = 0; i < escondida.length; i++){
            saida += escondida[i] * wEscSaida[i];//Encontra as saídas
        }
        // Faz o mesmo treinamento
        if (saida > 0.5)
            saida = 1;
        else
            saida = 0;
    }

    public  void  backward(){
        double [] err = new  double[escondida.length];//Array dos erros
        double  gError = 0;//Erro saída
        qtdtreino = 0;
        do {
            qtdtreino++;
            gError = 0;
            //inicia as entradas
            for (int p = 0; p < amostras.length; p++){
                for (int i = 0; i < entradas.length; i++){
                    entradas[i] = amostras[p][i];
                }
                forward();
                double  lErr = saidas[p] - saida;//Calcula o erro da saida
                gError += Math.abs(lErr);//Pega a parte absoluta
                //calcula o erro de cada perceptron da camada escondida
                for(int i = 0; i < escondida.length; i++){
                    err[i] = lErr * wEscSaida[i];//delta
                }


                //recalculo do erro do peso de cada sinápse entrada/intermediária 
                for (int i = 0; i < entradas.length; i++){
                    for (int j = 0; j < escondida.length; j++){
                        wEntEsc[i][j] += aprendizado * err[j] * entradas[i];
                    }
                }
                //recalculo do erro do peso de cada sinápse intermediária/saída 
                for (int i = 0; i < escondida.length; i++){
                    wEscSaida[i] += aprendizado * lErr * escondida[i];
                }
            }
        }while(gError != 0);//caso o erro seja zero a rede foi treinada
    }

    public void treino(){
        backward();
    }
    
    public void testa () {
        //Pesos da camada intermediária
        for(int i = 0; i < entradas.length; i++){
            for (int j = 0; j < wEntEsc[i].length; j++){       
                System.out.print("w["+i+""+j+"]"+wEntEsc[i][j]+" | ");//valores aleatórios de 0<x<1
            }
            System.out.println();
        }
        //Inicia pesos entre a camada oculta/saida
        for (int i = 0; i < wEscSaida.length; i++){
            int x = 0;
            System.out.print("w["+i+" "+x+"]"+wEscSaida[i]+"|");//valores aleatórios de 0<x<1
        }
        //Varre as amostras
        System.out.println("\nQuantidade de treinamentos"+qtdtreino);
        for (int p = 0; p < amostras.length; p++){
            System.out.print("\nXOR( ");
            for (int i = 0; i < entradas.length; i++){
                entradas[i] = amostras[p][i];
                System.out.print(amostras[p][i]+" ");
            }
            forward();
            System.out.print(") = "+saida);
        }
    }

    public  static  void  main(String[] args){
        MLP mlp = new MLP();
        mlp.treino();
        mlp.testa();
    }

}
