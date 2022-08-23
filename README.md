
<h1 align = "center">
    Processamento parcial de Matrizes
</h1>

<h4 align = "center">
    Este repositório contém a implementacao* de um algoritmo capaz de, a partir de uma Matriz maior contida em um arquivo, retirar somente a parte desejada para processamento, alem de salvar resultados anteriores em suam memoria, tornando o processo mais rapido e sutil para a CPU.  
</h4>

<h2 align="center"> 
   💡<strong><em>Algoritmo </em></strong>
</h2>


<p>
    <dl>
        <dt> 1. Criacao das Structs para os desejados tipos de dado; </dt>
        <dt> 2. Leitura do arquivo contendo a Matriz principal; </dt>
        <dt> 3. Obter as coordenadas que o usuario deseja; </dt>
        <dt> 4. Gerar uma "key" de acesso a Matriz; </dt>
        <dt> 5. Verificar se essa chave ja existe na memoria do programa; </dt>
        <dt> 6. Caso a chave exista: </dt> 
            <dd> 6.1 Imprimir a Matriz ligada a mesma. </dd>
        <dt> 7. Caso a chave nao exista: </dt>
            <dd> 7.1. Utilizar as coordenadas informadas pelo usuario anteriormente a fim de navegar pelo arquivo e encontrar as posicoes iniciais e finais da Matriz; </dd>
            <dd> 7.2. Transferir o conteudo referente as coordenadas a uma Matriz menor; </dd>
            <dd> 7.3. Utilizar a Matriz menor a fim de obter sua transposta;</dd>
            <dd> 7.4. Utilizando os resultados obtidos nos passos <strong> 7.2 </strong> e <strong> 7.3</strong>, realizar a multiplicacao entre as duas Matrizes; </dd>
            <dd> 7.5. Mostrar o resultado da multiplicacao ao usuario; </dd>
            <dd> 7.6. Salvar a Matriz resultante juntamente a sua chave em um <i>unordered_map</i>;</dd>
            <dd> </dd>
    </d1>
</p>

 <h2 align="center">
    👨‍💻
    <strong>
        <em> 
            Implementacao
        </em>    
    </strong>
</h2>

Inicialmente, foram criadas as **Structs** utilizadas no programa, sendo uma para os valores das Matrizes, denominada **_Data_**, e a outra, sendo responsavel por criar de fato o tipo desejado no programa, cujo nome eh **_Matrix_**, como pode ser visto abaixo: 

```c++
struct Data {
    int value;
};

struct Matrix {
    Data **Mat;
};
```

Vale salientar que o motivo do uso de ponteiros para a **Struct** **_Matrix_** se da pelo fato de nunca usufruir de valores estaticos, sempre variando de acordo com o desejo do usuario.

A partir do momento que se tem as **Structs** criadas, eh necessario questionar ao usuario quais os valores que limitam a Matriz desejada, sendo eles o **i inicial**, **j inicial**, **i final** e o **j final**. Como forma de obter esses valores, foi criada a funcao **_getCoordenates()_**, que recebe como parametro quatro enderecos de memoria de inteiros, inicializados dentro da main, pergunta as coordenadas desejadas para cada uma das supracitadas que, sem a necessidade de retornar, ja atualiza seus valores dentro da main: 

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

Tendo as coordenadas sido coletadas, eh chamada a funcao **_generateKey()_**, que eh do tipo **long long unsigned int** por um motivo: o tamanho que as coordenadas podem ter. A fim de evitar o estouro de buffer utilizando somente **int**, foi utilizada essa proposta para contornar a problematica. Na funcao enunciada anteriormente, as coordenadas digitadas pelo usuario sao passadas como parametro, e a chave segue a seguinte regra de formacao em texto:

<p align = "center">
    i_inicial + j_inicial + i_final + j_final
</p>

Entretanto, esses valores sao coletados como inteiro, portanto, existe a conversao de todos os valores acima para **std::string**, por meio da funcao **std::to_string**, feito isso para todas, eh realizada a concatencao de todas as strings, e novamente transformadas para inteiro, por meio da funcao **std::stoi**, sendo esse valor retornado a main. A implementacao pode ser visualizada abaixo:

```c++
long long unsigned int generateKey(int initial_i, int initial_j, int final_i, int final_j) {
    return stoi((to_string(initial_i) + to_string(initial_j) + to_string(final_i) + to_string(final_j)));
}
```

Apos esse processo, eh realizado um pequeno calculo a fim de se obter os parametros da Matriz, que serao importantes posteriormente no programa: $$i = (final_i - initial_i + 1)$$ $$j = (final_j - initial_j + 1)$$

Seguindo, chega a parte responsavel por toda a diferenca do programa: verificar se a Matriz ja foi processada anteriormente, por meio da funcao booleana **_verifyMemory()_**, que retornara **true** caso encontrar a existencia da Matriz e **false**, caso nao. Como parametros para essa funcao, sao passados o *unordered_map*, estrutura de dado utilizada para armazenar resultados, e um *long long unsigned int*, tipo de dado utilizado para chaves:

```c++
bool verifyMemory(unordered_map<long long unsigned int, Data**> memory, long long unsigned int key) {
    auto search = memory.find(key);
    if (search != memory.end()) {
        return true;
    }
    
    return false;
}
```

Partindo do pressuposto que a chave nao exista, significa que um novo processamento sera necessario. Para esse proposito, sao necessarias 3 variaveis excepcionais: **_mainMatrix_**, **_transposedMatrix_** e **_multipliedMatrix_**, todas do tipo *Data***, estrutura anteriormente criada e declaradas como ponteiros.

A fim de se obter a Matriz principal, sendo essa a desejada pelo usuario, eh chamada a funcao **_fillMatrix()_**, que recebe como parametro o nome do documento que contem a Matriz maior, assim como todas as coordenadas tidas via input.

Na sequencia, ja dentro da funcao, eh efetuada a leitura de arquivos conforme os padroes do **_C++_**, utilizando a biblioteca *_ifstream_*. Com o arquivo aberto, inicialmente almeja-se chegar a linha desejada da Matriz (i_inicial), para isso, eh realizado um looping que vai de 0 a (i_inicial - 1), sendo a proxima linha lida, a primeira desejada. A partir dessa etapa, eh aberto um looping **while** que eh executado ate chegar ao fim do arquivo. Nesse looping, eh utilizada a funcao **std::getline**, com tres parametros: o primeiro sendo o arquivo de qual estara sendo feita a leitura, o segundo, para qual variavel o conteudo sera copiado e, por fim, o terceiro sendo responsavel por tokenizar todos os valores da Matriz, utilizando como delimitador o caractere ' ' (espaco). Com isso, todas as "linhas de interesse" serao tokenizadas.  

A fim de controlar ate que o ponto o looping correra, foi criada a variavel *num_elements*, utilizada como forma de parar o looping uma vez que o contador chegue ao valor da mesma, que significara que todos os valores ja foram inseridos em um vetor auxiliar, que posteriormente sera passado a Matriz:
$$ numelements = (final_i - initial_i + 1) * (final_j - initial_j + 1) $$

A fim de controlar o caminhamento pelas devidas colunas, foi utilizada a variavel *j_coord*, a qual tinha a funcao de controlar qual era a "atual coluna" da leitura. Para que um elemento pudesse ser inserido no vetor auxiliar, a variavel supracitada deveria ser maior ou igual ao valor de *j_inicial* e menor ou igual ao valor de *j_final*, levando que ela era incrementada em um a cada inplementacao do looping. A fim de controlar erros e evitar que fossem inseridos valores indesejados, eh sempre realizada a verificacao de que, se *j_coord* for maior ou igual ao *j_final*, seu valor sera resetado a 0.

Para passar os valores ao vetor auxiliar, eh utilizada a funcao **std::stoi**, pegando como string, transformando a inteiro, sendo assim inseridas corretamente no vetor.

Apos a finalizacao do looping, eh utilizado o *Metodo da Bolha* como forma de passar os valores do vetor auxiliar a Matriz, retornando-a no ao fim da funcao. Pode ser visualizado abaixo como todo o contexto supracitado foi implementado: 

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

                if (j_coord >= final_j) {
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

Apos todo o processo citado, eh necessario obter a transposta da Matriz anterior. Para tal processo, eh utilizada a funcao **_getTransposedMatrix()_**, que recebe tres parametros, sendo o primeiro, o endereco de memoria da Matriz principal, uma vez que os valores dela serao necessarios para a criacao da Transposta, o numero de linhas e o numero de colunas, que serao simplesmente os valores de linhas e colunas da Matriz principal, porem invertidos (i = j e j = i). Os valores sao passados e a Matriz Transposta eh retornada: 

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

Tendo ambas as matrizes, o que resta eh realizar a multiplicacao de matrizes e, para tal, eh utilizada a funcao **_multiplyMatrices()_**. A funcao eh implementada da forma mais padrao possivel, com 4 parametros: o endereco de memoria da Matriz Principal, o endereco de memoria da Matriz Transposta, a coordenada da Matriz que sera o resultado (i obtido na Main) e, por fim, a quantidade de colunas da Matriz Transposta (j obtido na Main). A multiplicacao eh efetuada e a Matriz resultante eh retornado para a Main: 

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

Por fim, a Matriz resultante, juntamente a sua Key, sao inseridas no *unordered_map*, cuja variavel eh identificada por **_memory_**, utilizando a funcao built-in **_map::emplace_**, sendo os parametros, Key e Matriz.




