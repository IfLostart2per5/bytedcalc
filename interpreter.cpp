#include <vector>
#include <iostream>
//macro util ;)
#define INIT_ARRAY(type, name, size, value) type name[size]; \
  for (size_t i = 0; i < size; i++) \
    name[i] = value;

void err_message(int type, int idx, int j, int x, int y) {
    if (type == 1) 
      std::cerr << "ERR (at instruction index " << idx << "): Index " << j << " is out of range. ignoring instructions until a recovery-point (32 instruction)" << std::endl;
    else if (type == 2)
      std::cerr << "ERR (at instruction index " << idx << "): Stack indexers " << x << " and " << y << " is out of range. Ignoring instructions until a recovery-point (32 instruction)" << std::endl;
    else if (type == 3)
      std::cerr << "ERR (at instruction index " << idx << " to " << idx + 2 << "): invalid memory set. Ignoring instructions until a recovery-point (32 instruction) (tip: the memory size is just 100 slots ;) )" << std::endl;
    else if (type == 4)
      std::cerr << "ERR: (at instruction index " << idx << " to " << idx + 1 << "): invalid memory get. Ignoring instructions until a recovery-point (32 instruction). (tip: the memory size is just 100 slots ;) )" << std::endl;
    else if (type == 5)
      std::cerr << "ERR: (at instruction index " << idx << "): division by zero not allowed!. Ignoring instructions until a revovery-poimt (32 instruction)." << std::endl;
    else if (type == 6)
      std::cerr << "ERR: (at instruction index " << idx << "): invalid non-initialized memory access. Ignoring instructions until a recovery-point (32 instruction)." << std::endl;
  }


 std::vector<int> interpret(int values[], int valsize, int instructions[],int size, bool autoinc) {
  std::vector<int> stack;


  static int memory[100];
  static INIT_ARRAY(bool, memory_marking, 100, false);
  //indices rastreadores, j é o indice dos valores,e x e y são os indices da pilha
  int j = 0;
  int x = 0;
  int y = 1;
  bool errOcurred = false;


  for (int i = 0; i < size; i++) {
    //verifica se ja ocorreu um erro, se sim,entra em pânico
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
          err_message(1, i, j, x, y);
          errOcurred = true;
        }

        break;
      case 2:
        if (j > -1) {
          stack.pop_back();
          if (autoinc)
            j -= 1;
        } else {
          err_message(1, i, j, x, y);
          errOcurred = true;
        }

        break;
      case 3:
        //aqui ele faz algumas otimizações aritméticas simples, valendo pros outros operadores também
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
          err_message(2, i, j, x, y);
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
          err_message(2, i, j, x, y);
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
          err_message(2, i, j, x, y);
          errOcurred = true;
        }
        break;
      case 6:
        if (x < stack.size() && y < stack.size()) {
          if (stack[y] == 0) {
            err_message(5, i, j, x, y);
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
          err_message(2, i, j, x, y);
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
      //TODO: otimizar operações bit a bit
      case 9:
        if (x < stack.size() && y < stack.size()) {
        stack[x] &= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i, j, x, y);
          errOcurred = true;
        }
        break;
      case 10:
        if (x < stack.size() && y < stack.size()) {
        stack[x] |= stack[y];
        stack.erase(stack.begin() + y);
        } else {
          err_message(2, i, j, x, y);
          errOcurred = true;
        }
        break;
      case 11:
        if (y < stack.size()) {
          stack[y] = ~stack[y];
        } else {
         err_message(2, i, j, x, y);
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
          memory_marking[instructions[i + 1]] = true;
          i += 2;
        } else {
          err_message(3, i, j, x, y);
          errOcurred = true;
       
        }
        break;
      case 15:
        if (instructions[i + 1] < 100) {
          if (memory_marking[instructions[i + 1]]) {
            stack.push_back(memory[instructions[i + 1]]);
            i += 1;
          } else {
            err_message(6, i, j, x, y);
            errOcurred = true;
          }
        } else {
          err_message(4, i, j, x, y);
          errOcurred = true;
        }
        break;
      case 16:
        if (instructions[i + 1] < 100) {
          if (memory_marking[instructions[i + 1]]) {

            memory[instructions[i + 1]] = (int) NULL;
            memory_marking[instructions[i + 1]] = false;
            i += 1;
          } else {

            err_message(6, i, j, x, y);
            errOcurred = true;
          } 
        } else {
          err_message(4, i, j, x, y);
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
