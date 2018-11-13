#include "utils.H"

bool dir_exists(const char* path)
{
  struct stat st;
  return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

void hello()
{
  cout << "HI THERE, this is C++" << endl;
}

int getInt_range(int min, int max)
{
  int input;
    
  while(!(cin >> input) || input < min || input > max)
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please select a number between 1 and " << max << " "; 
  }
  cout << endl;

  return input;
}

