#include "solver.h"


/*************************** DECLARE YOUR HELPER FUNCTIONS HERE ************************/
/* Check if putting queen on (row, col) is valid. */
bool isValid(const std::vector<unsigned int> &queen_col_pos, 
			 const unsigned int &row, 
			 const unsigned int &col) {
	for (unsigned int i = 0; i < row; i++) {
		if (queen_col_pos[i] == col || abs(queen_col_pos[i] - col) == (row - i)) {
			return false;
		}
	}
	return true;
}

/* The actual sequential solver */
void actual_seq_solver(std::vector<std::vector<unsigned int>> &all_solns, 
					   std::vector<unsigned int> &curr_res, 
					   unsigned int row, 
					   const unsigned int &n) {
	/* Base case */
	if (row == n) {
		all_solns.push_back(curr_res);
		return;
	}

	for (unsigned int col = 0; col < n; col++) {
		if (isValid(curr_res, row, col)) {
			curr_res[row] = col;
			actual_seq_solver(all_solns, curr_res, row + 1, n);
			curr_res[row] = 0;
		}
	}
}

/* Calculate the next partial solution with k queens */
bool next_partial_solution(std::vector<unsigned int> &partial_solution, 
						   std::vector<unsigned int> &curr_res, 
						   unsigned int row,
						   const unsigned int &n, 
						   const unsigned int &k,
						   const bool & had_sol) {
	
	/* Base case */
	if (row == k) {
		partial_solution = curr_res;
		had_sol = true;
		return true;
	}

	bool found_sol = false;
	for (unsigned int col = row == k - 1 && had_sol ? curr_res[row] + 1 : curr_res[row]; col < n; col++) {
		if (isValid(curr_res, row, col)) {
			curr_res[row] = col;
			found_sol = next_partial_solution(partial_solution, curr_res, row + 1, n, k, had_sol);
			if (found_sol) {
				return true;
			}
			curr_res[row] = 0;
		}
	}

	return false;
}

/*************************** solver.h functions ************************/
void seq_solver(unsigned int n, std::vector<std::vector<unsigned int>> &all_solns) {

	// DONE: Implement this function

	/* Create current result */
	std::vector<unsigned int> curr_res (n, 0);

	/* Start actual solver */
	actual_seq_solver(all_solns, curr_res, 0, n);
}






void nqueen_master(unsigned int n,
				   unsigned int k,
				   std::vector<std::vector<unsigned int> >& all_solns) {




	// TODO: Implement this function

	/* Following is a general high level layout that you can follow
	 (you are not obligated to design your solution in this manner.
	  This is provided just for your ease). */


	/******************* STEP 1: Send one partial solution to each worker ********************/
	/*
	 * for (all workers) {
	 * 		- create a partial solution.
	 * 		- send that partial solution to a worker
	 * }
	 */


	/******************* STEP 2: Send partial solutions to workers as they respond ********************/
	/*
	 * while() {
	 * 		- receive completed work from a worker processor.
	 * 		- create a partial solution
	 * 		- send that partial solution to the worker that responded
	 * 		- Break when no more partial solutions exist and all workers have responded with jobs handed to them
	 * }
	 */

	/********************** STEP 3: Terminate **************************
	 *
	 * Send a termination/kill signal to all workers.
	 *
	 */

	int num_procs;
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Status stat;
	MPI_Request req;

	/* Create current result */
	std::vector<unsigned int> curr_res (n, 0);
	std::vector<unsigned int> partial_solution (k, 0);
	std::vector<unsigned int> res_send (n, 0);
	std::vector<unsigned int> res_recv (n, 0);
	bool had_sol = false, found_sol = false, found_all_sol = false, all_work_done = false;
	int src;

	/******************* STEP 1: Send one partial solution to each worker ********************/
	/* Find next partial solution for each worker, send them to the workers */
	for (int w = 0; w < num_procs; w++) {
		/* Find next partial solution */
		found_sol = next_partial_solution(partial_solution, curr_res, 0, n, k, had_sol);

		/* Send the solution to the worker */
		if (found_sol) {
			res_send = partial_solution;
			MPI_Send(&res_send[0], n, MPI_INT, w, 100, MPI_COMM_WORLD);
		} else {
			break;
		}
	}

	/******************* STEP 2: Send partial solutions to workers as they respond ********************/
	while (!found_all_sol && !all_work_done) {
		MPI_Irecv(&res_recv[0], n, MPI_INT, MPI_ANY_SOURCE, 101, MPI_COMM_WORLD, &req);
		found_sol = next_partial_solution(partial_solution, curr_res, 0, n, k, had_sol);
		MPI_Wait(&req, &stat);
		src = stat.MPI_SOURCE;
		res_send = partial_solution;
		MPI_Send(&res_send[0], n, MPI_INT, src, 100, MPI_COMM_WORLD);
	}
}

void nqueen_worker(	unsigned int n,
					unsigned int k) {



	// TODO: Implement this function

	// Following is a general high level layout that you can follow (you are not obligated to design your solution in this manner. This is provided just for your ease).

	/*******************************************************************
	 *
	 * while() {
	 *
	 * 		wait for a message from master
	 *
	 * 		if (message is a partial job) {
	 *				- finish the partial solution
	 *				- send all found solutions to master
	 * 		}
	 *
	 * 		if (message is a kill signal) {
	 *
	 * 				quit
	 *
	 * 		}
	 *	}
	 */


}



/*************************** DEFINE YOUR HELPER FUNCTIONS HERE ************************/
