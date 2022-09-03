
<h1 align = "center">
    Processamento parcial de Matrizes
</h1>

<h4 align = "center">
    Este repositório contém a implementação de um sistema de multiplicação de matrizes baseando-se em uma estratégia de segmentação em arquivo.
</h4>

<h2 align="center"> 
   💡<strong><em>Algoritmo </em></strong>
</h2>

<p>
    <dl>
        <dt> 1. Criação das Structs para os desejados tipos de dado; </dt>
        <dt> 2. Leitura do arquivo contendo a Matriz principal; </dt>
        <dt> 3. Obter as coordenadas que o usuário deseja; </dt>
        <dt> 4. Gerar uma "key" de acesso a Matriz; </dt>
        <dt> 5. Verificar se essa chave já existe na memória do programa; </dt>
        <dt> 6. Caso a chave exista: </dt> 
            <dd> 6.1 Imprimir a Matriz ligada a mesma. </dd>
        <dt> 7. Caso a chave nãoexista: </dt>
            <dd> 7.1. Utilizar as coordenadas informadas pelo usuário anteriormente a fim de navegar pelo arquivo e encontrar as posicoes iniciais e finais da Matriz; </dd>
            <dd> 7.2. Transferir o conteúdo referente as coordenadas a uma Matriz menor; </dd>
            <dd> 7.3. Utilizar a Matriz menor a fim de obter sua transposta;</dd>
            <dd> 7.4. Utilizando os resultados obtidos nos passos <strong> 7.2 </strong> e <strong> 7.3</strong>, realizar a multiplicação entre as duas Matrizes; </dd>
            <dd> 7.5. Mostrar o resultado da multiplicação ao usuário; </dd>
            <dd> 7.6. Salvar a Matriz resultante juntamente a sua chave em um <i>unordered_map</i>;</dd>
            <dd> </dd>
    </d1>
</p>

<h2 align="center">
    ⚠️
    <strong>
        <em>
            Observações Importantes
        </em>
    </strong>
</h2>

- Para o devido funcionamento do programa, atente-se aos espaços no final de cada uma das linhas:
    - Logo após os últimos valores, em **TODAS** as linhas devem terminar com um caractere de espaço.
- Os valores a serem inseridos não condizem com o padrão da linguagem C/C++. Com isso, o que deseja ser passado é que, a primeira linha é selecionada com o valor 1, não com o valor 0, e assim por diante, por exemplo:
    - Acessar da primeira linha à sétima linha, da terceira coluna à nona coluna:
       - I inicial = 1
       - J inicial = 3
       - I final = 7
       - J final = 9
- Caso deseje modificar a matriz presente no documento, será necessário atentar-se à primeira observação. Ademais, deve ser realizada uma alteração na linha **29** presente no arquivo **_"matrix.cpp"_**, e a variável **matrix_line_size** deve receber a quantidade de valores presentes por linha.

 <h2 align="center">
    👨‍💻
    <strong>
        <em> 
            Implementação
        </em>    
    </strong>
</h2>

Inicialmente, foram criadas as **Structs** utilizadas no programa, sendo uma para os valores das Matrizes, denominada **_Data_**, e a outra, sendo responsável por criar de fato o tipo desejado no programa, cujo nome é **_Matrix_**, como pode ser visto abaixo: 

```c++
struct Data {
    int value;
};

struct Matrix {
    Data **Mat;
};
```

Vale salientar que o motivo do uso de ponteiros para a **Struct** **_Matrix_** se da pelo fato de nunca usufruir de valores estáticos, sempre variando de acordo com o desejo do usuário.

A partir do momento que se tem as **Structs** criadas, é necessário questionar ao usuário quais os valores que limitam a Matriz desejada, sendo eles o **i inicial**, **j inicial**, **i final** e o **j final**. Como forma de obter esses valores, foi criada a função **_getCoordenates()_**, que recebe como parâmetro quatro endereços de memória de inteiros, inicializados dentro da main, pergunta as coordenadas desejadas para cada uma das supracitadas que, sem a necessidade de retornar, já atualiza seus valores dentro da main: 

```c++
void getCoordenates(int *initial_i, int *initial_j, int *final_i, int *final_j) {
    cout << "\t- Please inform the initial I coordenate: ";
    cin >> *initial_i;

    cout << "\t- Please inform the initial J coordenate: ";
    cin >> *initial_j;

    cout << "\t- Please inform the final I coordenate: ";
    cin >> *final_i;

    cout << "\t- Please inform the final J coordenate: ";
    cin >> *final_j;
}
```

Tendo as coordenadas sido coletadas, é chamada a função **_generateKey()_**, que é do tipo **long long unsigned int** por um motivo: o tamanho que as coordenadas podem ter. A fim de evitar o estouro de buffer utilizando somente **int**, foi utilizada essa proposta para contornar a problematica. Na função enunciada anteriormente, as coordenadas digitadas pelo usuário são passadas como parâmetro, e a chave segue a seguinte regra de formacao em texto:

<p align = "center">
    i_inicial + j_inicial + i_final + j_final
</p>

Entretanto, esses valores são coletados como inteiro, portanto, existe a conversão de todos os valores acima para **std::string**, por meio da função **std::to_string**, feito isso para todas, é realizada a concatenação de todas as strings, e novamente transformadas para inteiro, por meio da função **std::stoi**, sendo esse valor retornado a main. A implementação pode ser visualizada abaixo:

```c++
long long unsigned int generateKey(int initial_i, int initial_j, int final_i, int final_j) {
    return stoi((to_string(initial_i) + to_string(initial_j) + to_string(final_i) + to_string(final_j)));
}
```

Apos esse processo, é realizado um pequeno calculo a fim de se obter os parâmetros da Matriz, que serão importantes posteriormente no programa: $$i = (final_i - initial_i + 1)$$ $$j = (final_j - initial_j + 1)$$

Seguindo, chega a parte responsável por toda a diferenca do programa: verificar se a Matriz já foi processada anteriormente, por meio da função booleana **_verifyMemory()_**, que retornara **true** caso encontrar a existencia da Matriz e **false**, caso não. Como parâmetros para essa função, são passados o *unordered_map*, estrutura de dado utilizada para armazenar resultados, e um *long long unsigned int*, tipo de dado utilizado para chaves:

```c++
bool verifyMemory(unordered_map<long long unsigned int, Data**> memory, long long unsigned int key) {
    auto search = memory.find(key);
    if (search != memory.end()) {
        return true;
    }
    
    return false;
}
```

Partindo do pressuposto que a chave não exista, significa que um novo processamento será necessário. Para esse propósito, são necessarias 3 variaveis excepcionais: **_mainMatrix_**, **_transposedMatrix_** e **_multipliedMatrix_**, todas do tipo *Data***, estrutura anteriormente criada e declaradas como ponteiros.

A fim de se obter a Matriz principal, sendo essa a desejada pelo usuário, é chamada a função **_fillMatrix()_**, que recebe como parâmetro o nome do documento que contem a Matriz maior, assim como todas as coordenadas tidas via input.

Na sequencia, já dentro da função, é efetuada a leitura de arquivos conforme os padrões do **_C++_**, utilizando a biblioteca *_ifstream_*. Com o arquivo aberto, inicialmente almeja-se chegar a linha desejada da Matriz (i_inicial), para isso, é realizado um looping que vai de 0 a (i_inicial - 1), sendo a próxima linha lida, a primeira desejada. A partir dessa etapa, é aberto um looping **while** que é executado ate chegar ao fim do arquivo. Nesse looping, é utilizada a função **std::getline**, com três parâmetros: o primeiro sendo o arquivo de qual estara sendo feita a leitura, o segundo, para qual variavel o conteúdo será copiado e, por fim, o terceiro sendo responsável por tokenizar todos os valores da Matriz, utilizando como delimitador o caractere ' ' (espaco). Com isso, todas as "linhas de interesse" serão tokenizadas.  

A fim de controlar ate que o ponto o looping correra, foi criada a variavel *num_elements*, utilizada como forma de parar o looping uma vez que o contador chegue ao valor da mesma, que significara que todos os valores já foram inseridos em um vetor auxiliar, que posteriormente será passado a Matriz:
$$ numelements = (final_i - initial_i + 1) * (final_j - initial_j + 1) $$

A fim de controlar o caminhamento pelas devidas colunas, foi utilizada a variavel *j_coord*, a qual tinha a função de controlar qual era a "atual coluna" da leitura. Para que um elemento pudesse ser inserido no vetor auxiliar, a variavel supracitada deveria ser maior ou igual ao valor de *j_inicial* e menor ou igual ao valor de *j_final*, levando que ela era incrementada em um a cada inplementacao do looping. A fim de controlar erros e evitar que fossem inseridos valores indesejados, é sempre realizada a verificacao de que, se *j_coord* for maior ou igual ao *j_final*, seu valor será resetado a 0.

Para passar os valores ao vetor auxiliar, é utilizada a função **std::stoi**, pegando como string, transformando a inteiro, sendo assim inseridas corretamente no vetor.

Apos a finalizacao do looping, é utilizado o *Metodo da Bolha* como forma de passar os valores do vetor auxiliar a Matriz, retornando-a no ao fim da função. Pode ser visualizado abaixo como todo o contexto supracitado foi implementado: 

```c++
Data** fillMatrix(string docName, int initial_i, int initial_j, int final_i, int final_j) {
    Data** mainMatrix = 0;
    mainMatrix = new Data*[final_i - initial_i + 1];
    
    int cont = 0, num_elements = (final_i - initial_i + 1) * (final_j - initial_j + 1);
    int aux[num_elements];
    int j_coord = 0;
    string line;
    ifstream myfile;
    myfile.open(docName);
    
    int a = 0;

    if (myfile.is_open()) {
        for (int i = 0; i < initial_i - 1; i++) {
            getline(myfile, line);
        }

        while(!myfile.eof()) {
            while(getline(myfile, line, ' ') && cont < num_elements) {
                j_coord++;

                if (j_coord >= initial_j && j_coord <= final_j) {
                    aux[a] = stoi(line);
                    a++;
                    cont++;
                }

                if (j_coord >= matrix_line_size) {
                    j_coord = 0;
                }
            }
        }
    }

    a = 0;

    for (int i = 0; i < (final_i - initial_i + 1); i++) {
        mainMatrix[i] = new Data[(final_j - initial_j + 1)];
        for (int j = 0; j < (final_j - initial_j + 1); j++) {
            mainMatrix[i][j].value = aux[a];
            a++;
        }
    }

    return mainMatrix;
}
```

Apos todo o processo citado, é necessário obter a transposta da Matriz anterior. Para tal processo, é utilizada a função **_getTransposedMatrix()_**, que recebe três parâmetros, sendo o primeiro, o endereço de memória da Matriz principal, uma vez que os valores dela serão necessários para a criação da Transposta, o número de linhas e o número de colunas, que serão simplesmente os valores de linhas e colunas da Matriz principal, porem invertidos (i = j e j = i). Os valores são passados e a Matriz Transposta é retornada: 

```c++
Data** getTransposedMatrix(Data **mainMatrix, int lines, int columns) {
    Data** transposedMatrix = 0;
    transposedMatrix = new Data*[columns];

    for (int i = 0; i < columns; i++) {
        transposedMatrix[i] = new Data[lines];
        for (int j = 0; j < lines; j++) {
            transposedMatrix[i][j].value = mainMatrix[j][i].value;
        }
    }

    return transposedMatrix;
}
```

Tendo ambas as matrizes, o que resta é realizar a multiplicação de matrizes e, para tal, é utilizada a função **_multiplyMatrices()_**. A função é implementada da forma mais padrao possivel, com 4 parâmetros: o endereço de memória da Matriz Principal, o endereço de memória da Matriz Transposta, a coordenada da Matriz que será o resultado (i obtido na Main) e, por fim, a quantidade de colunas da Matriz Transposta (j obtido na Main). A multiplicação é efetuada e a Matriz resultante é retornada para a Main: 

```c++
Data** multiplyMatrices(Data **mainMatrix, Data **transposedMatrix, int size, int columnsTransposed) {
    Data** multipliedMatrix = 0;
    multipliedMatrix = new Data*[size];
    int sum;

    for (int i = 0; i < size; i++) {
        multipliedMatrix[i] = new Data[size];
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < columnsTransposed; k++) {
                sum += (mainMatrix[i][k].value * transposedMatrix[k][j].value);
            }
 
            multipliedMatrix[i][j].value = sum;
        }
    }

    return multipliedMatrix;
}
```

Por fim, a Matriz resultante, juntamente a sua Key, são inseridas no *unordered_map*, cuja variavel é identificada por **_memory_**, utilizando a função built-in **_map::emplace_**, sendo os parâmetros, Key e Matriz.

Ainda há a possibilidade de que a Matriz desejada já tenha sido anteriormente processada. Como forma de evitar tal acontecimento, é verificado se o conteúdo que se procura já está gravado no **_std::unordered_map_** chamado de **memory**. Para tal, inicialmente é feita a verificação por meio da função **_verifyMemory()_**:

```c++
bool verifyMemory(unordered_map<long long unsigned int, Data**> memory, long long unsigned int key) {
    auto search = memory.find(key);
    if (search != memory.end()) {
        return true;
    }
    
    return false;
}
```

A função acima retornará **true** caso encontre a chave desejada, portanto, impossibilitando o programa de realizar todo o processo novamente, chamando somente a função **_printMatrix()_**, para mostrar a Matriz ao usuário. A junção de todo o processo supracitado foi implementado dentro do arquivo **main.cpp**, da forma exibida abaixo:

```c++
if(!verifyMemory(memory, key)) {
    cout << endl << endl << "\t\t~ This is this Matrix's key: " << key << endl << endl;

    cout << "\t\t\t\t~ This is the Main Matrix ~" << endl << endl;
    mainMatrix = fillMatrix(docName, initial_i, initial_j, final_i, final_j);
    printMatrix(mainMatrix, i, j);

    cout << endl << "\t\t\t~ This is the Transposed of the Main Matrix ~" << endl << endl;
    transposedMatrix = getTransposedMatrix(mainMatrix, i, j);
    printMatrix(transposedMatrix, j, i);

    cout << endl <<"\t\t~ This is the multiplication between the two matrices above ~" << endl << endl;
    multipliedMatrix = multiplyMatrices(mainMatrix, transposedMatrix, i, j);
    printMatrix(multipliedMatrix, i, i);

    memory.emplace(key, multipliedMatrix);
} else {
    cout << endl << endl << "\t\t- This matrix has already been processed, here is the result: " << endl << endl;
    memoryMatrix = memory[key];
    printMatrix(memoryMatrix, i, i);
}
```
 <h2 align="center">
    🔧
    <strong>
        <em> 
            Resultados Esperados
        </em>    
    </strong>
</h2>

Ao utilizar o arquivo de texto presente nesse repositório, a Matriz lida e tida como arquivo input será a que segue:


<table align = "center">
  <tr>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>10</td>
    <td>11</td>
    <td>12</td>
    <td>13</td>
    <td>14</td>
    <td>15</td>
    <td>16</td>
    <td>17</td>
    <td>18</td>
    <td>19</td>
    <td>20</td>
  </tr> 
  <tr>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>0</td>
    <td>2</td>
    <td>1</td>
    <td>2</td>
    <td>5</td>
    <td>1</td>
    <td>6</td>
    <td>1</td>
    <td>8</td>
    <td>9</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>8</td>
    <td>9</td>
    <td>2</td>
  </tr>
  <tr>
    <td>7</td>
    <td>8</td>
    <td>7</td>
    <td>0</td>
    <td>4</td>
    <td>9</td>
    <td>8</td>
    <td>7</td>
    <td>4</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>7</td>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>9</td>
    <td>7</td>
    <td>9</td>
  </tr>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>5</td>
    <td>6</td>
    <td>8</td>
    <td>7</td>
    <td>3</td>
    <td>9</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>2</td>
    <td>6</td>
    <td>8</td>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
  </tr>
  <tr>
    <td>5</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>8</td>
    <td>6</td>
    <td>9</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>6</td>
  </tr>
  <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>1</td>
    <td>4</td>
    <td>8</td>
    <td>7</td>
    <td>9</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>7</td>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>4</td>
    <td>5</td>
    <td>8</td>
    <td>7</td>
    <td>1</td>
    <td>9</td>
  </tr>
    <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>2</td>
    <td>5</td>
    <td>4</td>
  </tr>
  <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>1</td>
    <td>4</td>
    <td>8</td>
    <td>7</td>
    <td>9</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>7</td>
  </tr>
  <tr>
    <td>5</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>8</td>
    <td>6</td>
    <td>9</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>6</td>
  </tr>
  <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>2</td>
    <td>5</td>
    <td>4</td>
  </tr>
  <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>1</td>
    <td>4</td>
    <td>8</td>
    <td>7</td>
    <td>9</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>7</td>
  </tr>
  <tr>
    <td>5</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>4</td>
    <td>8</td>
    <td>6</td>
    <td>9</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>6</td>
  </tr>
  <tr>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>9</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>7</td>
    <td>8</td>
    <td>5</td>
    <td>2</td>
    <td>1</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>2</td>
    <td>5</td>
    <td>4</td>
  </tr>
  <tr>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>0</td>
    <td>4</td>
    <td>9</td>
    <td>8</td>
    <td>7</td>
    <td>4</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>7</td>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>6</td>
    <td>9</td>
    <td>7</td>
    <td>9</td>
  </tr>
  <tr>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>0</td>
    <td>2</td>
    <td>1</td>
    <td>2</td>
    <td>5</td>
    <td>1</td>
    <td>6</td>
    <td>1</td>
    <td>8</td>
    <td>9</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>8</td>
    <td>9</td>
    <td>2</td>
  </tr>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>5</td>
    <td>6</td>
    <td>8</td>
    <td>7</td>
    <td>3</td>
    <td>9</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>2</td>
    <td>6</td>
    <td>8</td>
    <td>1</td>
    <td>2</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
  </tr>
  <tr>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>0</td>
    <td>2</td>
    <td>1</td>
    <td>2</td>
    <td>5</td>
    <td>1</td>
    <td>6</td>
    <td>1</td>
    <td>8</td>
    <td>9</td>
    <td>3</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>8</td>
    <td>9</td>
    <td>2</td>
</tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
    <td>1</td>
    <td>2</td>
    <td>3</td>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>0</td>
    <td>4</td>
    <td>5</td>
    <td>6</td>
    <td>7</td>
    <td>8</td>
    <td>9</td>
  </tr>
</table>

<p align="center">
    <i>
        Tabela 1: Matriz principal, que será processada pelo programa.
    </i>
</p>

Em seguida, suponhamos que o usuário decidiu inserir as seguintes coordenadas:

<p align="center">
    <strong>
        I inicial: 18 <br>
        J inicial: 15 <br>
        I final: 20<br>
        J final: 20<br>
    </strong>
</ṕ>

##### Caso a Matriz ainda não tenha sido processada anteriormente, isto é, caso o usuário ainda não tenha digitado os valores acima para I e J, se a seguinte sequência de resultados:

A Matriz recortada será:

<table align="center">
    <tr>
        <td>1</td>
        <td>2</td>
        <td>3</td>
        <td>4</td>
        <td>5</td>
        <td>6</td>
    </tr>
    <tr>
        <td>7</td>
        <td>8</td>
        <td>9</td>
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr>
        <td>4</td>
        <td>5</td>
        <td>6</td>
        <td>7</td>
        <td>8</td>
        <td>9</td>
    </tr>
</table>

Após o "recorte" da Matriz, sua transposta será mostrada ao usuário, o que se espera, ainda com esses valores, é a seguinte Matriz:

<table align="center">
    <tr>
        <td>1</td>
        <td>7</td>
        <td>4</td>
    </tr>
    <tr>
        <td>2</td>
        <td>8</td>
        <td>5</td>
    </tr>
    <tr>
        <td>3</td>
        <td>9</td>
        <td>6</td>
    </tr>
    <tr>
        <td>4</td>
        <td>1</td>
        <td>7</td>
    </tr>
    <tr>
        <td>5</td>
        <td>2</td>
        <td>8</td>
    </tr>
    <tr>
        <td>6</td>
        <td>3</td>
        <td>9</td>
    </tr>
</table>

Por fim, a multiplicação entre ambas as matrizes é realizada, com os valores acima, o resultado esperado é visto abaixo: 

<table align="center">
    <tr>
        <td>91</td>
        <td>82</td>
        <td>154</td>
    </tr>
    <tr>
        <td>82</td>
        <td>208</td>
        <td>172</td>
    </tr>
    <tr>
        <td>154</td>
        <td>172</td>
        <td>271</td>
    </tr>
</table>

##### Caso a Matriz já tenha sido anteriomente processada, ou seja, caso o usuário já a tenha digitado anteriormente na execução do programa, aparecerá uma mensagem de aviso, juntamente à Matriz multiplicada.

E o resultado esperado não pode ser diferente:

<table align="center">
    <tr>
        <td>91</td>
        <td>82</td>
        <td>154</td>
    </tr>
    <tr>
        <td>82</td>
        <td>208</td>
        <td>172</td>
    </tr>
    <tr>
        <td>154</td>
        <td>172</td>
        <td>271</td>
    </tr>
</table>

Vale salientar que tais valores são apresentados para o usuário por meio de seu respectivo terminal.



<h2 align="center">
    🔧
    <strong>
        <em> 
            Compilação e Execução
        </em>    
    </strong>
</h2>

| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação             

É recomendável utilizar o comando **make clean** antes de partir para o **make** e sequencialmente **make run**.





