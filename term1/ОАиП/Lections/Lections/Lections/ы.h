#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  int N = 0, max = -1000000, indexMaxi = 0, indexMaxj = 0, p = 0, indexm = 0, indexn = 0;
  cout << "Vvedite N = ";
  cin >> N;

  float** arr = new float* [N];
  for (int count = 0; count < N; count++)
    arr[count] = new float[N];

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      cin >> arr[i][j];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << arr[i][j] << "  ";
    }
    cout << endl;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (max <= arr[i][j]) {
        max = arr[i][j];
        indexMaxi = i;
        indexMaxj = j;
          }
      }
    }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == N - 1 && j == N - 1) {
        indexm = i;
        indexn = j;
      }
    }
  }

  cout << "Samiy bolshoi element - " << max << endl;
  
  p = arr[indexMaxi][indexMaxj];
  arr[indexMaxi][indexMaxj] = arr[indexm][indexn];
  arr[indexm][indexn] = p;
    
    for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << arr[i][j] << "  ";
    }
    cout << endl;
  }


}

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int N, M;

    cout << "Vvedite N i M (N > 9, M > 9):" << endl << "N = ";
    cin >> N;
    cout << endl << "M = ";
    cin >> M;
    cout << endl;

    if (N <= 9) {
        do {
            cout << "N dolzhno bit bolshe 9, vvedite N: " << endl << "N = ";
            cin >> N;
            cout << endl;
        } while (N <= 9);
    }

    if (M <= 9) {
        do {
            cout << "M dolzhno bit bolshe 9, vvedite M: " << endl << "M = ";
            cin >> M;
            cout << endl;
        } while (M <= 9);
    }

    cout << "Suschestvuut x i y takie, chto: " << endl << "0 < x <= N" << endl << "0 < y <= M" << endl << endl << "sin(x)^2 + sin(y^2) > 0.9" << endl << endl;

    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= M; y++) {
            if (pow(sin(x), 2) + sin(pow(y, 2)) > 0.9) {
                cout << "x = " << x << " " << "y = " << y << endl;
            }
        }
    }
}

#include <iostream>

using namespace std;

int Min(int a, int b, int c)

{
    if (b < a) {
        a = b;
    }
    if (c < a) {
        a = c;
    }
    cout << a << endl;
    return 0;
}

int main()
{
    int a, b, c;
    cout << "Vvedite 3 chisla cherez probel: ";
    cin >> a >> b >> c;

    Min(a, b, c);
}

#include <iostream>
#include <string>

using namespace std;

int main()
{
  string str;
  int check = 0, ind = 0, temp;
  cout << "Vvedite stroku: ";
  getline(cin, str);

  for (int i = 0; i < size(str); ++i) {
    if (str[i] == ',') {
      check++;
      ind = i;
    }
  }

  cout << "Kolichestvo zapyatih -  " << check << endl << endl;

  if (check > 3) {
    cout << "Tak kak kolichestvo zapyatih bolshe treh, odna iz nih zamenyaetsya tochkoi." << endl;
    str[ind] = '.';
    }

  if (check <= 3) {
    for (int i = 0; i < size(str); ++i) {
      if (str[i] == ',') {
        temp = i;
        while (str[temp + 1] != '\0') {
          str[temp] = str[temp + 1];
          temp++;
        }
      }
    }
  }

  cout << str << endl ;
}
