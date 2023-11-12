#pragma once
#include "Libs.h"
#include "Elements.h"
#define MAXNOFR 100

int NumberOfPoints = 1; //n
int NumberOfRezistors = 0;
float mas[MAXNOFR][MAXNOFR][MAXNOFR];
int m[MAXNOFR][MAXNOFR];
float e = 0.0000000001;
int FLAG = 0;

void printmas() {
	for (int i = 0; i < NumberOfPoints; i++) {
		for (int j = 0; j < NumberOfPoints; j++) {
			cout << mas[i][j][0];
			if (mas[i][j][1] != 0) cout << "*";
			cout << " ";
		}
		cout << endl;
	}
	cout << NumberOfPoints << " " << NumberOfRezistors << endl;
}
int StartNull(Rezistor_list& rezistor_list) {

	Rezistor__ptr ptr = rezistor_list.link_begin;
	int ptr_index = 0;
	if (!rezistor_list.len) return -1;
	do {
		if (ptr->value.c_col1 != black || ptr->value.c_col2 != black) {
			ptr = ptr->link_next;
			rezistor_list.clear(ptr_index--);
			ptr_index++;
			continue;
		}
		ptr = ptr->link_next;
		ptr_index++;
	} while (ptr != nullptr);

	for (int i = 0; i < MAXNOFR; i++) {
		for (int j = 0; j < MAXNOFR; j++) {
			for (int k = 0; k < MAXNOFR; k++) {
				mas[i][j][k] = 0;
			}
			m[i][j] = 0;
		}
	}
	NumberOfRezistors = 0;
	NumberOfPoints = 1;
	FLAG = 0;
	return 0;
}
//занулить все у всех элементов
void EndNull(Line_list& line_list, Rezistor_list& rezistor_list) {
	Line_ptr ptr = line_list.link_begin;
	Rezistor__ptr __ptr = rezistor_list.link_begin;
	do {
		ptr->value.index = -1;
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	do {
		while (__ptr->value.l_index.len) __ptr->value.l_index.clear();
		while (__ptr->value.r_index.len) __ptr->value.r_index.clear();
		__ptr->value.l_conectflag = false;
		__ptr->value.r_conectflag = false;
		//__ptr->value.l_index = 0;
		//__ptr->value.r_index = 0;
		__ptr->value.l_con_flag_in = 0;
		__ptr->value.r_con_flag_in = 0;
		__ptr = __ptr->link_next;
	} while (__ptr != nullptr);
}

int SetNumbersOfPoints(Line_list& line_list) {
	Line_ptr ptr = line_list.link_begin;
	if (!line_list.len) return -1;

	do {
		if (ptr->value.rb1 == nullptr && ptr->value.rb2 == nullptr) {
			bool flag = false;
			if (ptr->value.rc11 != nullptr)
				if (ptr->value.rc11->value.l_conectflag) {
					ptr->value.index = ptr->value.rc11->value.l_con_flag_in;
					flag = true;
				}
			if (ptr->value.rc12 != nullptr)
				if (ptr->value.rc12->value.r_conectflag) {
					ptr->value.index = ptr->value.rc12->value.r_con_flag_in;
					flag = true;
				}
			if (ptr->value.rc21 != nullptr)
				if (ptr->value.rc21->value.l_conectflag) {
					ptr->value.index = ptr->value.rc21->value.l_con_flag_in;
					flag = true;
				}
			if (ptr->value.rc22 != nullptr)
				if (ptr->value.rc22->value.r_conectflag) {
					ptr->value.index = ptr->value.rc22->value.r_con_flag_in;
					flag = true;
				}
			if (!flag) {
				if (ptr->value.rc11 != nullptr) {
					ptr->value.rc11->value.l_conectflag = true;
					ptr->value.rc11->value.l_con_flag_in = ptr->value.index = NumberOfPoints;
				}
				if (ptr->value.rc21 != nullptr) {
					ptr->value.rc21->value.l_conectflag = true;
					ptr->value.rc21->value.l_con_flag_in = ptr->value.index = NumberOfPoints;
				}
				if (ptr->value.rc12 != nullptr) {
					ptr->value.rc12->value.r_conectflag = true;
					ptr->value.rc12->value.r_con_flag_in = ptr->value.index = NumberOfPoints;
				}
				if (ptr->value.rc22 != nullptr) {
					ptr->value.rc22->value.r_conectflag = true;
					ptr->value.rc22->value.r_con_flag_in = ptr->value.index = NumberOfPoints;
				}
				NumberOfPoints++;
			}
		}
		if (ptr->value.rb1 != nullptr && ptr->value.rb2 != nullptr) return -1;
		if (ptr->value.rb1 != nullptr) ptr->value.index = 0;
		if (ptr->value.rb2 != nullptr) ptr->value.index = -2;
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	ptr = line_list.link_begin;
	do {
		if (ptr->value.index == -2) ptr->value.index = NumberOfPoints;
		ptr = ptr->link_next;
	} while (ptr != nullptr);
	NumberOfPoints++;
	return 0;
}

int SetNumberOfRezistors(Rezistor_list& rezistor_list) {
	NumberOfRezistors = rezistor_list.len;
	if (!NumberOfRezistors) return -1;
	return 0;
}

inline float fun_par_chet(int y, int x) {
	float s = 0;
	for (int i = 0; i <= m[y][x]; i++) {
		s += 1 / mas[y][x][i];
	}
	return 1 / s;
}

inline void proverka_lisnee() {
	int flag = 0, s = 0;
	while (flag == 0) {
		int f = 0;
		for (int i = 1; i < NumberOfPoints - 1; i++) {
			for (int j = 0; j < NumberOfPoints; j++) {
				if (mas[i][j][0] != 0) {
					s++;
				}
			}
			if (s == 1) {
				f = 1;
				for (int j = 0; j < NumberOfPoints; j++) {
					mas[i][j][0] = 0;
					mas[j][i][0] = 0;
				}
			}
			s = 0;
		}
		if (f == 0) {
			flag = 1;
		}
	}
}

void InputValue(Line_list& line_list, Rezistor_list& rezistor_list) {
	float c;
	int b, a;
	Line_ptr ptr = line_list.link_begin;
	do {
		if (ptr->value.rc11 != nullptr && !ptr->value.rc11->value.l_index.contains(ptr->value.index)) ptr->value.rc11->value.l_index.append(ptr->value.index);
		if (ptr->value.rc12 != nullptr && !ptr->value.rc12->value.r_index.contains(ptr->value.index)) ptr->value.rc12->value.r_index.append(ptr->value.index);
		if (ptr->value.rc21 != nullptr && !ptr->value.rc21->value.l_index.contains(ptr->value.index)) ptr->value.rc21->value.l_index.append(ptr->value.index);
		if (ptr->value.rc22 != nullptr && !ptr->value.rc22->value.r_index.contains(ptr->value.index)) ptr->value.rc22->value.r_index.append(ptr->value.index);
		ptr = ptr->link_next;
	} while (ptr != nullptr);

	Rezistor__ptr r_ptr = rezistor_list.link_begin;
	gdd_list::__list<int>* lptr;
	gdd_list::__list<int>* rptr;
	do {

		lptr = r_ptr->value.l_index.link_begin;
		if (lptr == nullptr) continue;
		do {

			rptr = r_ptr->value.r_index.link_begin;
			if (rptr == nullptr) continue;
			do {

				a = lptr->value;
				b = rptr->value;
				c = (float)r_ptr->value.value.to();

				if (c == 0) c = e;

				if (mas[a][b][0] == 0) {
					mas[a][b][0] = c;
					mas[b][a][0] = c;
				}
				else {
					m[a][b]++;
					m[b][a]++;
					mas[a][b][m[a][b]] = c;
					mas[b][a][m[b][a]] = c;
				}

				rptr = rptr->link_next;
			} while (rptr != nullptr);

			lptr = lptr->link_next;
		} while (lptr != nullptr);

		r_ptr = r_ptr->link_next;
	} while (r_ptr != nullptr);

	for (int i = 0; i < MAXNOFR; i++) {
		for (int j = 0; j < MAXNOFR; j++) {
			if (m[i][j] != 0) {
				mas[i][j][0] = fun_par_chet(i, j);
				mas[j][i][0] = fun_par_chet(j, i);
				for (int k = 1; k <= m[i][j]; k++) {
					mas[i][j][k] = 0;
					mas[j][i][k] = 0;
				}
				m[i][j] = 0;
				m[j][i] = 0;
			}
		}
	}
	proverka_lisnee();
}

inline void fun_treyg_preob(int n1, int n2, int n3) {
	NumberOfPoints++;
	float sum = mas[n1][n2][0] + mas[n1][n3][0] + mas[n3][n2][0];
	mas[n1][NumberOfPoints - 1][0] = mas[n1][n2][0] * mas[n1][n3][0] / sum;
	mas[NumberOfPoints - 1][n1][0] = mas[n1][n2][0] * mas[n1][n3][0] / sum;
	mas[n2][NumberOfPoints - 1][0] = mas[n1][n2][0] * mas[n2][n3][0] / sum;
	mas[NumberOfPoints - 1][n2][0] = mas[n1][n2][0] * mas[n2][n3][0] / sum;
	mas[n3][NumberOfPoints - 1][0] = mas[n1][n3][0] * mas[n2][n3][0] / sum;
	mas[NumberOfPoints - 1][n3][0] = mas[n1][n3][0] * mas[n2][n3][0] / sum;

	mas[n1][n2][0] = 0;
	mas[n2][n1][0] = 0;
	mas[n3][n2][0] = 0;
	mas[n2][n3][0] = 0;
	mas[n1][n3][0] = 0;
	mas[n3][n1][0] = 0;
}


inline void fun_treyg() {
	int fh = 0;
	for (int i = 0; i < NumberOfPoints; i++) {
		for (int j = 0; j < NumberOfPoints; j++) {
			if (mas[i][j][0] != 0) {
				for (int I = j + 1; I < NumberOfPoints; I++) {
					if (mas[j][I][0] != 0 && mas[i][I][0] != 0) {
						FLAG = 1;
						fun_treyg_preob(i, j, I);
						fh = 1;
						break;
					}
				}
				if (fh == 1) {
					break;
				}
			}
		}
		if (fh == 1) {
			break;
		}
	}
}


inline void fun_zvezda_preob(int i, int n1, int n2, int n3) {
	mas[n1][n2][0] = mas[n1][i][0] + mas[n2][i][0] + mas[n1][i][0] * mas[n2][i][0] / mas[n3][i][0];
	mas[n2][n1][0] = mas[n1][i][0] + mas[n2][i][0] + mas[n1][i][0] * mas[n2][i][0] / mas[n3][i][0];
	mas[n2][n3][0] = mas[n3][i][0] + mas[n2][i][0] + mas[n3][i][0] * mas[n2][i][0] / mas[n1][i][0];
	mas[n3][n2][0] = mas[n3][i][0] + mas[n2][i][0] + mas[n3][i][0] * mas[n2][i][0] / mas[n1][i][0];
	mas[n1][n3][0] = mas[n3][i][0] + mas[n1][i][0] + mas[n3][i][0] * mas[n1][i][0] / mas[n2][i][0];
	mas[n3][n1][0] = mas[n3][i][0] + mas[n1][i][0] + mas[n3][i][0] * mas[n1][i][0] / mas[n2][i][0];

	for (int j = 0; j < NumberOfPoints; j++) {
		mas[i][j][0] = 0;
		mas[j][i][0] = 0;
	}
}


inline void fun_zvezda() {
	for (int i = 1; i < NumberOfPoints - 1; i++) {
		int s = 0;
		for (int j = 0; j < NumberOfPoints; j++) {
			if (mas[i][j][0] != 0) {
				s++;
			}
		}
		if (s == 3) {
			int y = 0, n1, n2, n3;
			for (int j = 0; j < NumberOfPoints; j++) {
				if (mas[i][j][0] != 0) {
					if (y == 0) {
						n1 = j;
					}
					if (y == 1) {
						n2 = j;
					}
					if (y == 2) {
						n3 = j;
					}
					y++;
				}
			}
			fun_zvezda_preob(i, n1, n2, n3);
		}
		break;
	}
}

inline void fun_posl(int q) {
	int t = 0;
	for (int i = 0; i < NumberOfPoints; i++) {
		for (int j = 0; j < NumberOfPoints; j++) {
			if (mas[i][j][0] != 0) {
				t++;
			}
		}
	}
	if (t == 4) {
		double S = 0;
		for (int i = 0; i < NumberOfPoints; i++) {
			for (int j = 0; j < NumberOfPoints; j++) {
				if (mas[i][j][0] != 0) {
					S += mas[i][j][0];
					mas[i][j][0] = 0;
					mas[j][i][0] = 0;
				}
			}
		}
		mas[0][q - 1][0] = S;
		mas[q - 1][0][0] = S;
		FLAG = 1;
	}
	else {
		for (int i = 1; i < NumberOfPoints; i++) {
			if (i != q - 1) {
				int s = 0, fl = 0;
				for (int j = 0; j < NumberOfPoints; j++) {
					if (mas[i][j][0] != 0) { s++; }
				}
				if (s == 2) {
					FLAG = 1;
					int n1, n2, qgb = 0;
					float s = 0;
					for (int j = 0; j < NumberOfPoints; j++) {
						if (mas[i][j][0] != 0) {
							if (qgb == 0) { n1 = j; s += mas[i][j][0]; mas[i][j][0] = 0; mas[j][i][0] = 0; qgb++; }
							if (qgb == 1) { n2 = j; s += mas[i][j][0]; mas[i][j][0] = 0; mas[j][i][0] = 0; }
						}
					}
					if (mas[n1][n2][0] == 0) {
						mas[n1][n2][0] = s;
						mas[n2][n1][0] = s;
					}
					else {
						m[n1][n2]++;
						m[n2][n1]++;
						mas[n1][n2][m[n1][n2]] = s;
						mas[n2][n1][m[n2][n1]] = s;
					}
					break;
				}
			}
		}
	}
}


inline void fun_paral() {
	for (int i = 0; i < NumberOfPoints; i++) {
		for (int j = 0; j < NumberOfPoints; j++) {
			if (m[i][j] != 0) {
				mas[i][j][0] = fun_par_chet(i, j);
				mas[j][i][0] = fun_par_chet(j, i);
				m[i][j] = 0;
				m[j][i] = 0;
				FLAG = 1;
			}
		}
	}
}

int proverka(int q) {
	int f = 0, s = 0;
	for (int i = 0; i < NumberOfPoints; i++)
		for (int j = 0; j < NumberOfPoints; j++)
			if (mas[i][j][0] != 0) { s++; }

	//cout << m[0][q - 1] <<  " " << s << " - " << endl;
	if (m[0][q - 1] == 0 && s == 2) {
		f = 1;
	}
	return f;
}

float fun(int q) {
	int flag = 0;
	while (flag == 0) {
		fun_posl(q);
		fun_paral();
		if (FLAG == 0) {
			fun_treyg();
		}
		if (FLAG == 0) {
			fun_zvezda();
		}
		if (proverka(q) == 1) {
			if (mas[0][q - 1][0] < e * 10) {
				return 0;
			}
			else {
				return mas[0][q - 1][0];
			}
			flag = 1;
		}
		FLAG = 0;
	}
}