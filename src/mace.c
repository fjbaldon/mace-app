// Name: mace.c
// Purpose: Does a lot of stuff
// Author: Francis Baldon

#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS macro, system()
#include <string.h> // strcmp(), strlen()
#include <unistd.h> // sleep()

#define MAX_BUF_LENGTH 1024 
#define DEF_CHOICE 0
#define BACK -1
#define EXIT 0 

void start_prog(void); // starts the program

/* random cosmetics */
void clear_con(void); // clears the console
void print_loading_anim(void); // adds a 3 sec delay
void set_margin(void); // adds a margin above and left of text
void align_err_str(char* str); // uniforms error messages 

/* main prompts */
int authenticate(void); // gets and verifies the password
int ask_go_back(void); // returns EXIT or BACK
int ask_menu_opt(void); // returns a integer choice

/* int, float, & string input/parsers */
int get_int(void);
float get_float(void);
void get_string(char* string, size_t size);

/* choice and password validators */
int verify_int_choice(int choice);
int verify_str_pass(const char* ADMIN_PASS, char* pass);

/* menu and sub_menu displayers */
void print_menu(void);
void print_exit_dialog(void);
void print_sea_bullet_menu(void);
/**/ void print_manila(void);
/**/ void print_calc_cebu(void);
/**/ void print_calc_siargao(void);
void print_atm_transac_menu(void);
/**/ void print_calc_atm_dposit(float* blance, float* dposits);
/**/ void print_calc_atm_wdraw(float* blance, float* wdraws);
/**/ void print_calc_atm_blance(float* blance, float* dposits, float* wdraws);
void print_other_apps_menu(void);
/**/ void print_students_grade_menu(void);
/**/ /**/ void print_calc_elisa(void);
/**/ /**/ void print_calc_noel(void);
/**/ void print_converter(void);

/* logic for the menus */
int start_menu(void);
int start_sea_bullet(void);
int start_atm_transac(void);
int start_other_apps(void);
int start_students_grade(void);

int main(void) {
	start_prog();
	return EXIT_SUCCESS;
}

void clear_con(void) {
	system("clear");
	return;
}

void print_loading_anim(void) {
	puts("\n");
	fputs("\tProcessing .", stdout);
	fflush(stdout);
	sleep(1);
	fputs(".", stdout);
	fflush(stdout);
	sleep(1);
	fputs(".\n", stdout);
	fflush(stdout);
	return;
}

void set_margin(void) {
	puts("\n");
	printf("\t");
	return;
}

void align_err_str(char* str) {
	puts("");
	printf("\t%s\n", str);
	printf("\t>> ");
}

void start_prog(void) {
	clear_con();
	while (!authenticate()) {
		if (authenticate()) {
			break;
		}
	}
	if (start_menu() == EXIT) {
		print_exit_dialog();
		return;
	}
	return;
}

int authenticate(void) {
	const char ADMIN_PASS[] = "1234"; 
	char pass[MAX_BUF_LENGTH] = "";
	int is_ok = 0;

	set_margin();
	fputs("Enter password: ", stdout);
	get_string(pass, sizeof(pass));
	if (verify_str_pass(ADMIN_PASS, pass)) {
		return 1;
	} else {
		printf("\tWrong password!");
	}
	return is_ok;
}

int get_int(void) {
	char buf[MAX_BUF_LENGTH];
	int c, value = 0;

	while (1) {
		if (fgets(buf, MAX_BUF_LENGTH, stdin) == NULL) {
			align_err_str("Invalid input. Please enter an integer.");
			continue;
		}
		if (buf[strlen(buf) - 1] != '\n') {
			align_err_str("Input too long. Please try again.");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		buf[strlen(buf) - 1] = '\0';
		if (sscanf(buf, "%d", &value) == 1) {
			break;
		} else {
			align_err_str("Error reading input. Please try again.");
		}
	}
	return value;
}

float get_float(void) {
	char buf[MAX_BUF_LENGTH];
	float value = 0.0;
	int c;

	while (1) {
		if (fgets(buf, MAX_BUF_LENGTH-1, stdin) == NULL) {
			align_err_str("Invalid input. Please enter a float.");
			continue;
		}
		if (buf[strlen(buf) - 1] != '\n') {
			align_err_str("Input too long. Please try again.");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		buf[strlen(buf) - 1] = '\0';
		if (sscanf(buf, "%f", &value) == 1) {
			return value;
		} else {
			align_err_str("Error reading input. Please try again.");
		}
	}
	return value;
}

void get_string(char* string, size_t size) {
	char buf[MAX_BUF_LENGTH];
	int c;

	while (1) {
		if (fgets(buf, size, stdin) == NULL) {
			align_err_str("Invalid input. Please enter a string.");
			continue;
		}
		if (buf[strlen(buf) - 1] != '\n') {
			align_err_str("Input too long. Please try again.");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}
		buf[strlen(buf) - 1] = '\0';
		if (sscanf(buf, "%[^\n]", string) == 1) {
			return;
		} else {
			align_err_str("Error reading input. Please try again.");
		}
	}
	return;
}

int verify_str_pass(const char* ADMIN_PASS, char* pass) {
	if (!strcmp(ADMIN_PASS, pass)) {
		return 1;
	}
	return 0;
}

int verify_int_choice(int choice) {
	if (choice > 0 && choice < 5) {
		return 1;
	}
	return 0;
}

void print_menu(void) {
	set_margin();
	puts("\tKRISTOFF MACE");
	puts("\t\t Loon, Bohol\n");
	puts("\t[1] SEA BULLET CORPORATION");
	puts("\t[2] ATM TRANSACTION");
	puts("\t[3] OTHER APPS");
	puts("\t[4] EXIT\n");
	fputs("\tSELECT #: ", stdout);
	return;
}

int start_menu(void) {
	int choice = DEF_CHOICE;
	int val_return = EXIT;

	while (1) {
		clear_con();
		print_menu();
		choice = ask_menu_opt();
		switch (choice) {
			case 1:
				clear_con();
				val_return = start_sea_bullet();
			break;
			case 2:
				clear_con();
				val_return = start_atm_transac();
			break;
			case 3:
				clear_con();
				val_return = start_other_apps();
			break;
			case 4:
				return EXIT;
			break;
			default:
			continue;
		}
		if (val_return == EXIT) {
			return EXIT;
		}
	}
	return val_return;
}

void print_sea_bullet_menu(void) {
	set_margin();
	puts("\tSEA BULLET CORPORATION");
	puts("\t\t   Tagbilaran City\n");
	puts("\tTRIP SCHEDULE: ");
	puts("\t[1] MANILA");
	puts("\t[2] CEBU");
	puts("\t[3] SIARGAO");
	puts("\t[4] BACK\n");
	fputs("\tSELECT #: ", stdout);
	return;
}

int start_sea_bullet() {
	int choice = DEF_CHOICE;
	int val_return = EXIT;

	while (1) {
		clear_con();
		print_sea_bullet_menu();
		choice = ask_menu_opt();
		switch (choice) {
			case 1:
				clear_con();
				print_manila();
				val_return = ask_go_back();
			break;
			case 2:
				clear_con();
				print_calc_cebu();
				val_return = ask_go_back();
			break;
			case 3:
				clear_con();
				print_calc_siargao();
				val_return = ask_go_back();
			break;
			case 4:
				clear_con();
				return BACK;
			break;
		}
		if (val_return == EXIT) {
			return EXIT;
		}
	}
	return val_return;
}

void print_manila(void) {
	set_margin();
	puts("\tMabuhay!!");
	return;
}

void print_calc_cebu(void) {
	float freight = 0.0, vat = 0.0, tfee = 0.0, fare = 0.0, dscount = 0.0;

	set_margin();
	puts("E N T E R\n");
	fputs("\tFreight                ", stdout);
	freight = get_float();
	fputs("\tVAT                    ", stdout);
	vat = get_float();
	fputs("\tTerminal fee           ", stdout);
	tfee = get_float();
	fare = 500.00 + freight + vat + tfee;
	if (fare < 1500.00) {
		dscount = fare * 0.10;
	} else {
		dscount = fare * 0.15;
	}
	set_margin();
	puts("R E S U L T S\n");
	printf("\tFARE                %6.2f\n", fare);
	printf("\tDISCOUNT            %6.2f\n", dscount);
	printf("\tDISCOUNTED FARE     %6.2f\n", fare - dscount);
	return;
}

void print_calc_siargao(void) {
	char fname[64] = "", lname[64] = ""; 
	float others = 0.0, tax = 0.0, fare = 0.0, dscount = 0.0;
	int age = 0;

	set_margin();
	puts("E N T E R\n");
	fputs("\tFirst name        ", stdout);
	get_string(fname, sizeof(fname));
	fputs("\tLast name         ", stdout);
	get_string(lname, sizeof(lname));
	fputs("\tAge               ", stdout);
	age = get_int();
	fputs("\tOther charges     ", stdout);
	others = get_float();
	fputs("\tTaxes             ", stdout);
	tax = get_float();
	fare = 1000.00 + others + tax;
	if (age < 60) {
		dscount = fare * 0.15;
	} else {
		dscount = fare * 0.25;
	}
	set_margin();
	puts("R E S U L T S\n");
	printf("\tFIRST NAME        %s\n", fname);
	printf("\tLAST NAME         %s\n", lname);
	printf("\tAGE               %d\n", age);
	printf("\tFARE              %6.2f\n", fare);
	printf("\tDISCOUNT          %6.2f\n", dscount);
	printf("\tDISCOUNTED FARE   %6.2f\n", fare - dscount);
	return;
}

void print_atm_transac_menu(void) {
	set_margin();
	puts("\tATM TRANSACTION\n");
	puts("\t[1] DEPOSIT");
	puts("\t[2] WITHDRAW");
	puts("\t[3] BALANCE");
	puts("\t[4] EXIT\n");
	fputs("\tSELECT #: ", stdout);
	return;
}

int start_atm_transac(void) {
	static float blance = 0.0; 
	static float dposits = 0.0; 
	static float wdraws = 0.0;
	int choice = DEF_CHOICE;
	int val_return = EXIT;

	while (1) {
		clear_con();
		print_atm_transac_menu();
		choice = ask_menu_opt();
		switch (choice) {
			case 1:
				clear_con();
				print_calc_atm_dposit(&blance, &dposits);
				val_return = ask_go_back();
			break;
			case 2:
				clear_con();
				print_calc_atm_wdraw(&blance, &wdraws);
				val_return = ask_go_back();
			break;
			case 3:
				clear_con();
				print_calc_atm_blance(&blance, &dposits, &wdraws);
				val_return = ask_go_back();
			break;
			case 4:
				return EXIT;
			break;
			default: 
			continue;
		}
		if (val_return == EXIT) {
			return EXIT;
		}
	}
	return val_return;
}

void print_calc_atm_dposit(float* blance, float* dposits) {
	float t_dposit = 0.0;

	puts("\n");
	printf("\tB A L A N C E : %9.2f\n\n", *blance);
	fputs("\tEnter amount to deposit:     ", stdout);
	t_dposit = get_float();
	print_loading_anim();
	*dposits += t_dposit;
	*blance += t_dposit;
	set_margin();
	puts(">> Transaction successful! <<");
	printf("\tYour new balance is: PHP %9.2f\n", *blance);
	return;
}

void print_calc_atm_wdraw(float* blance, float* wdraws) {
	float t_wdraw = 0.0;

	if (*blance < 100.0) {
		set_margin();
		puts(">> Transaction failed. <<");
		puts("\tYou currently do not have enough funds to proceed the transaction");
		return;
	}
	puts("\n");
	printf("\tB A L A N C E : %9.2f\n\n", *blance);
	fputs("\tEnter amount to withdraw:    ", stdout);
	t_wdraw = get_float();
	print_loading_anim();
	if (t_wdraw > *blance) {
		set_margin();
		puts(">> Transaction failed. <<");
		puts("\tMake sure the amount you'll withdraw is lesser than the amount of your current balance.");
		return;
	}
	if (*blance - t_wdraw < 100) {
		set_margin();
		puts(">> Transaction failed. <<");
		puts("\tYou need to have at least 100 PHP left in your account.");
		return;
	}
	*wdraws += t_wdraw;
	*blance = *blance - t_wdraw;
	set_margin();
	puts(">> Transaction successful! <<");
	printf("\tYour new balance is: PHP %9.2f\n", *blance);
	return;
}

void print_calc_atm_blance(float* blance, float* dposits, float* wdraws) {
	print_loading_anim();
	set_margin();
	printf("DEPOSITED          PHP %9.2f\n", *dposits);
	printf("\tWITHDRAWN          PHP %9.2f\n", *wdraws);
	set_margin();
	printf("CURRENT BALANCE    PHP %9.2f\n", *blance);
	return;
}

void print_other_apps_menu(void) {
	puts("\n");
	puts("\t\tOTHER APPS");
	puts("\t\tCATEGORIES:\n");
	puts("\t[1] STUDENT'S GRADE");
	puts("\t[2] CONVERTER");
	puts("\t[3] BACK\n");
	fputs("\tSELECT #: ", stdout);
	return;
}

int start_other_apps(void) {
	int choice = DEF_CHOICE;
	int val_return = EXIT;

	while (1) {
		clear_con();
		print_other_apps_menu();
		choice = ask_menu_opt();
		while (choice == 4) {
			printf("\n\tInvalid choice.\n\t>> ");
			choice = ask_menu_opt();
		}
		switch (choice) {
			case 1:
				clear_con();
				val_return = start_students_grade();
			break;
			case 2:
				clear_con();
				print_converter();
				val_return = ask_go_back();
			break;
			case 3:
				clear_con();
				return BACK;
			break;
			default:
			continue;
		}
		if (val_return == EXIT) {
			return EXIT;
		}
	}
	return val_return;
}

void print_students_grade_menu(void) {
	set_margin();
	puts("\t\t\t STUDENT'S GRADE");
	puts("\t\t\t\tRATING PERCENTAGE\n");
	puts("\t[1] ELISA \tMAJOR EXAMS(40%) PROJECTS(35%) QUIZZES(25%)");
	puts("\t[2] NOEL  \tMAJOR EXAMS(40%) PROJECTS(30%) QUIZZES(20%)");
	puts("\t[3] BACK\n");
	fputs("\tSELECT #: ", stdout);
	return;
}

int start_students_grade(void) {
	int choice = DEF_CHOICE;
	int val_return = EXIT;

	while (1) {
		clear_con();
		print_students_grade_menu();
		choice = ask_menu_opt();
		while (choice == 4) {
			printf("\n\tInvalid choice.\n\t>> ");
			choice = ask_menu_opt();
		}
		switch (choice) {
			case 1:
				clear_con();
				print_calc_elisa();
				val_return = ask_go_back();
			break;
			case 2:
				clear_con();
				print_calc_noel();
				val_return = ask_go_back();
			break;
			case 3:
				clear_con();
				return BACK;
			break;
			default: 
			continue;
		}
		if (val_return == EXIT) {
			return EXIT;
		}
	}
	return val_return;
}

void print_calc_elisa(void) {
	int quiz = 0, p_quiz = 0, proj = 0, p_proj = 0, exam = 0, p_exam = 0;
	float grade = 0.0;

	set_margin();
	puts("You have chosen Elisa.");
	fputs("\n\tQUIZZES:    ", stdout);
	quiz = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_quiz = get_int();
	fputs("\n\tPROJECTS:   ", stdout);
	proj = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_proj = get_int();
	fputs("\n\tEXAMS:      ", stdout);
	exam = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_exam = get_int();

	grade = ((( (float)quiz / (float)p_quiz) * 50) + 50) * 0.25;
	grade += ((( (float)proj / (float)p_proj) * 50) + 50) * 0.35;
	grade += ((( (float)exam / (float)p_exam) * 50) + 50) * 0.40;
	set_margin();
	printf(">> ELISA's GRADE: %.2f\n", grade);
	return;
}

void print_calc_noel(void) {
	int quiz = 0, p_quiz = 0, proj = 0, p_proj = 0, exam = 0, p_exam = 0;
	float grade = 0.0;

	set_margin();
	puts("You have chosen Noel.");
	fputs("\n\tQUIZZES:    ", stdout);
	quiz = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_quiz = get_int();
	fputs("\n\tPROJECTS:   ", stdout);
	proj = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_proj = get_int();
	fputs("\n\tEXAMS:      ", stdout);
	exam = get_int();
	fputs("\tMAX SCORE:  ", stdout);
	p_exam = get_int();

	grade = ((( (float)quiz / (float)p_quiz) * 50) + 50) * 0.20;
	grade += ((( (float)proj / (float)p_proj) * 50) + 50) * 0.30;
	grade += ((( (float)exam / (float)p_exam) * 50) + 50) * 0.40;
	set_margin();
	printf(">> NOEL's GRADE: %.2f\n", grade);
	return;
}

void print_converter(void) {
	set_margin();
	puts("\tOpps!");
	return;
}

int ask_go_back(void) {
	char str[MAX_BUF_LENGTH];
	int result = EXIT;

	set_margin();
	while (1) {
		fputs("BACK [y] | EXIT [n]: ", stdout);
		get_string(str, sizeof(str));
		if (!(strcmp(str, "yes") && strcmp(str, "y"))) {
			return BACK;
		} else if (!(strcmp(str, "no") && strcmp(str, "n"))) {
			return EXIT;
		} else {
			puts("\tInvalid choice.");
		}
	}
	return result;
}

int ask_menu_opt(void) {
	int choice = DEF_CHOICE;

	while (1) {
		choice = get_int();
		if (verify_int_choice(choice)) {
			return choice;
		} else {
			align_err_str("Invalid choice.");
		} 	
	}
	return choice;
}

void print_exit_dialog(void) {
	set_margin();
	puts("Exited.\n\n");
	return;
}
