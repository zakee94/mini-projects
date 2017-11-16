#include <iostream>
#include <string>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

using namespace std;
string curr_dir;

void init_directory() {
  char* dir = (char*)malloc(sizeof(char)*64);
  getcwd(dir, 64);
  curr_dir = string(dir);
  free(dir);
}

void change_directory() {
  string curr_dir_dummy;

  cout << "\nEnter custom directory : ";
  cin.ignore();
  getline(cin, curr_dir_dummy);

  if (!chdir(curr_dir_dummy.c_str())) {
    cout << "\nDirectory change success !";
    curr_dir = curr_dir_dummy;
  }
  else
    cout << "\nError, dir_not_changed !";
}

DIR* directory_pointer() {
  DIR *dp = opendir(curr_dir.c_str());
  if (dp == NULL)
    cout << "Error, dp_pointer = NULL !\n";

  return dp;
}

void batch_rename() {
  string cus_name;
  char rnm_ch;

  struct dirent *dir_files = NULL;

  DIR *dp = directory_pointer();

  cout << ":: BATCH RENAMING::\n";
  while ((dir_files = readdir(dp)) != NULL) {
    if (string(dir_files->d_name) == "." || string(dir_files->d_name) == "..") {}
		else {
      cout << "\nName : " << dir_files->d_name << "\n";

      cout << "Rename(Y/N) : ";
      cin >> rnm_ch;

      if (rnm_ch == 'Y' || rnm_ch == 'y') {
        cout << "Enter new name : ";
        cin.ignore();
        getline(cin, cus_name);

      if (!rename(dir_files->d_name, cus_name.c_str()))
        cout << "Rename Success !";
      else
        cout << "Rename Error !";
      }
    }
  }
}

void batch_utility(int condition) {
  string append_str, crop_str;
  int condition41_i = 0, condition42_i = 0;
  int i = 0, n;

  if (condition == 31 || condition == 32) {
    cout << "Enter string to join : ";
    cin.ignore();
    getline(cin, append_str);
  }

  if (condition == 51 || condition == 52) {
    cout << "Enter num of char of index : ";
    cin >> n;
  }

  if (condition == 2) {
    cout << "Enter string to crop : ";
    cin.ignore();
    getline(cin, crop_str);
  }

  struct dirent *dir_files = NULL;

  DIR *dp = directory_pointer();

  cout << ":: BATCH JOINING::\n";
  while ((dir_files = readdir(dp)) != NULL) {
    if (string(dir_files->d_name) == "." || string(dir_files->d_name) == "..") {}
		else {
      cout << "\nName : " << dir_files->d_name << "\n";

      if (condition == 2)
      if (!rename(dir_files->d_name, (string(dir_files->d_name).replace(string(dir_files->d_name).find(crop_str), crop_str.length(), "")).c_str()))
        cout << "Rename Success !";
      else
        cout << "Rename Error !";

      if (condition == 31)
      if (!rename(dir_files->d_name, (append_str + string(dir_files->d_name)).c_str()))
        cout << "Rename Success !";
      else
        cout << "Rename Error !";

      if (condition == 32)
      if (!rename(dir_files->d_name, (string(dir_files->d_name) + append_str).c_str()))
        cout << "Rename Success !";
      else
        cout << "Rename Error !";

      if (condition == 41) {
        condition41_i++;

        if (!rename(dir_files->d_name, (to_string(condition41_i) + ". " + string(dir_files->d_name)).c_str()))
          cout << "Rename Success !";
        else
          cout << "Rename Error !";
      }

      if (condition == 42) {
        condition42_i++;

        if (!rename(dir_files->d_name, (string(dir_files->d_name) + "-" + to_string(condition42_i)).c_str()))
          cout << "Rename Success !";
        else
          cout << "Rename Error !";
      }

      if (condition == 51)
        if (!rename(dir_files->d_name, string(dir_files->d_name).substr(n, strlen(dir_files->d_name)-1).c_str()))
          cout << "Rename Success !";
        else
          cout << "Rename Error !";

      if (condition == 52)
        if (!rename(dir_files->d_name, string(dir_files->d_name).substr(0, strlen(dir_files->d_name)-n).c_str()))
          cout << "Rename Success !";
        else
          cout << "Rename Error !";
    }
  }
}

void selector() {
  int base_choice, rename_choice, join_choice;
  int give_serial_choice, remove_serial_choice;

  cout << "\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
  cout << "\n|   BATCH RENAMING UTILITY   |";
  cout << "\n|----------------------------|\n";


  cout << "\nEnter 1 for renaming choices";
  cout << "\nEnter 2 to get current directory";
  cout << "\nEnter 3 to change working directory";
  cout << "\nEnter 4 to exit";

    do {
      cout << "\n\nPlease select base choice :\n";
      cin >> base_choice ;
    switch(base_choice) {
      case 1:
      cout << "\nEnter 1 to batch rename";
      cout << "\nEnter 2 to crop name";
      cout << "\nEnter 3 to join name";
      cout << "\nEnter 4 give serial indexing";
      cout << "\nEnter 5 to remove serial indexing";
      cout << "\nEnter 6 to GO BACK";


      do {
        cout << "\n\nPlease select rename choice :\n";
        cin >> rename_choice;
      switch(rename_choice) {
        case 1:
        batch_rename();
        break;
        case 2:
        batch_utility(2);
        break;
        case 3:
        cout << "\nEnter 1 to join at front";
        cout << "\nEnter 2 to join at end\n";
        cin >> join_choice;

        switch(join_choice) {
          case 1:
          batch_utility(31);
          break;
          case 2:
          batch_utility(32);
          break;
          default:
          break;
        }
        break;
        case 4:
        cout << "\nEnter 1 to give index at front";
        cout << "\nEnter 2 to give index at end\n";
        cin >> give_serial_choice;

        switch(give_serial_choice) {
          case 1:
          batch_utility(41);
          break;
          case 2:
          batch_utility(42);
          break;
          default:
          break;
        }
        break;
        case 5:
        cout << "\nEnter 1 to remove index from front";
        cout << "\nEnter 2 to remove index from end\n";
        cin >> remove_serial_choice;

        switch(remove_serial_choice) {
          case 1:
          batch_utility(51);
          break;
          case 2:
          batch_utility(52);
          break;
          default:
          break;
        }
        break;
        default:
        break;
      }
    }
    while(rename_choice != 6);
    break;

      case 2:
      cout << "\nCurrent Directory : " << curr_dir << "\n";
      break;

      case 3:
      change_directory();
      break;

      case 4:
      cout << "GoodBye !\n";
      exit(0);

      default :
      cout << "\nWrong choice ! Please try again.\n";
      break;
    }
  }
  while(1);
}

int main(int argc, char const *argv[]) {
  init_directory();
  selector();
  return 0;
}
