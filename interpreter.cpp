#include <vector>
#include <iostream>


 std::vector<int> interpret(int values[], int valsize, int instructions[],int size, bool autoinc) {
  std::vector<int> stack;
  static int memory[100];
  int j = 0;
  int x = 0;
  int y = 1;
  bool errOcurred = false;


  auto err_message = [&](int type, int idx) {
    if (type == 1) 
      std::cout << "ERR (at instruction index " << idx << "): Index " << j << " is out of range. ignoring instructions until a recovery-point (32 instruction)" << std::endl;
    else if (type == 2)
      std::cout << "ERR (at instruction index " << idx << "): Stack indexers " << x << " and " << y << " is out of range. Ignoring instructions until a recovery-point (32 instruction)" << std::endl;
    else if (type == 3)
      std::cout << "ERR (at instruction index " << idx << " to " << idx + 2 << "): invalid memory set. Ignoring instructions until a recovery-point (32 instruction) (tip: the memory size is just 100 slots ;) )" << std::endl;
    else if (type == 4)
      std::cout << "ERR: (at instruction index " << idx << " to " << idx + 1 << "): invalid memory get. Ignoring instructions until a recovery-point (32 instruction). (tip: the memory size is just 100 slots ;) )" << std::endl;
    else if (type == 5)
      std::cout << "ERR: (at instruction index " << idx << "): division by zero not allowed!. Ignoring instructions until a revovery-poimt (32 instruction)." << std::endl;

  };


  for (int i = 0; i < size; i++) {
    if (errOcurred) {
      if (instructions[i] != 32) {
        
        continue;
      } else {
        errOcurred = false;
        i++;
      }
    }

    switch(instructions[i]) { 
      case 0:
        goto end;
      case 1:
        if (j < valsize) {
          stack.push_back(values[j]);
          if (autoinc)
            j += 1;
        } else {
          err_message(1, i);
          errOcurred = true;
        }

        break;
      case 2:
        if (j > -1) {
          stack.pop_back();
          if (autoinc)
            j -= 1;
        } else {
          err_message(1, i);
          errOcurred = true;
        }

        break;
      case 3:
        if(x < stack.size() && y < stack.size()) {
          if (!(stack[x] == 0 && stack[y] == 0)) {
            stack[x] += stack[y];
            stack.erase(stack.begin() + y);
          } else if (stack[x] == 0 && stack[y] != 0) {
            stack[x] = stack[y];
            stack.erase(stack.begin() + y);
          } else if (stack[y] == 0 && stack[x] != 0) {
            stack.erase(stack.begin() + y);
          } else {
            stack.erase(stack.begin() + y);
          }
        } else {
          err_message(2, i);
          errOcurred = true;
        }
        break;
      case 4:
        if (x < stack.size() && y < stack.size()) {
          if (!(stack[x] == 0 || stack[y] == 0)) {
            stack[x] *= stack[y];
            stack.erase(stack.begin() + y);
          } else if (stack[x] == 0 || stack[y] == 0) {
            stack[x] = 0;
            stack.erase(stack.begin() + y);

          } else if (stack[x] == 1 && stack[y] != 1){
            stack[x] = stack[y];
            stack.erase(stack.begin() + y);
          }
        } else {
          err_message(2, i);
          errOcurred = true;
        }
        break;
      case 5:
        if (x < stack.size() && y < stack.size()) {
          if (stack[y] == 0) {
            stack.erase(stack.begin() + y);
            break;
          }
        stack[x] -= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i);
          errOcurred = true;
        }
        break;
      case 6:
        if (x < stack.size() && y < stack.size()) {
          if (stack[y] == 0) {
            err_message(5, i);
            errOcurred = true;
            break;
          }
        if (stack[y] == 1) {
          stack.erase(stack.begin() + y);
          break;
        } else if (stack[y] == stack[x]) {
          stack[x] = 1;
          stack.erase(stack.begin() + y);
          break;
        }
        stack[x] /= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i);
          errOcurred = true;
        };
        break;
      case 7:
        x += 1;
        y += 1;
        break;
      case 8:
        if ((x == 0) || (y == 1))
          break;
        x -= 1;
        y -= 1;
        break;
      case 9:
        if (x < stack.size() && y < stack.size()) {
        stack[x] &= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i);
          errOcurred = true;
        }
        break;
      case 10:
        if (x < stack.size() && y < stack.size()) {
        stack[x] |= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i);
          errOcurred = true;
        }
        break;
      case 11:
        if (y < stack.size()) {
          stack[y] = ~stack[y];
        } else {
         err_message(2, i);
         errOcurred = true;
        }
        break;
      case 12:
        if (j < valsize) {
          j += 1;
        }
        break;
      case 13:
        if (j > -1) {
          j -= 1;
        }
        break;
      case 14:
        if (instructions[i + 1] < 100) {
        memory[instructions[i + 1]] = instructions[i + 2];
        i += 2;
        } else {
          err_message(3, i);
          errOcurred = true;
       
        }
        break;
      case 15:
        if (instructions[i + 1] < 100) {
        stack.push_back(memory[instructions[i + 1]]);
        i += 1;
        } else {
          err_message(4, i);
          errOcurred = true;
        }
        break;

    }
  }

  end:
    return stack;

}

#ifdef ALLOW_AUTOINC_AS_OPTIONAL
std::vector<int> interpret(int values[], int valsize, int instructions[], int size) {
  return interpret(values, valsize, instructions, size, true);
}

#endif
