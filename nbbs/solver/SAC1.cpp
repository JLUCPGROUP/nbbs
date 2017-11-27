/*
 * SAC1.cpp
 *
 *  Created on: 2016年11月17日
 *      Author: leezear
 */

#include "SAC1.h"
using namespace Gecode;
namespace cudacp {
SAC1::SAC1(GModel* model) :
	model(model) {
	// TODO Auto-generated constructor stub

}

SAC1::~SAC1() {
	// TODO Auto-generated destructor stub
}

bool SAC1::enforce() const {
	bool modified = false;
	SpaceStatus status = model->status();

	if (status == SS_FAILED)
		return false;

	do {
		modified = false;
		for (int i = 0; i < model->vs.size(); i++) {
			IntVar v = model->vs[i];
			Int::IntView view(v);
			//for (IntVarValues k(view); k();++k) {
			for (int j = view.min(); j <= view.max(); ++j) {
				if (view.in(j)) {
					GModel *s = static_cast<GModel*>(model->clone());
					Int::IntView sv(s->vs[i]);
					sv.eq(*s, j);
					status = s->status();
					if (status == SS_FAILED) {
						view.nq(*model, j);
						status = model->status();
						if (status == SS_FAILED)
							return false;

						modified = true;
					}
					delete s;
				}
			}
		}
	} while (modified);

	for (int i = 0; i < 20; i++) {
		GModel *s = static_cast<GModel*>(model->clone());
		rel(*s, s->vs[0] == 0);
		rel(*s, s->vs[3] == 0);
		rel(*s, s->vs[7] == i);
		status = s->status();
		printf("(%d,%d,%d,%d,%d,%d):", 0, 0, 3, 0, 7, i);

		if (status == SS_BRANCH) {
			printf(" sat!\n");
		}
		else if (status == SS_SOLVED) {
			s->print();
		}
		else {
			printf(" unsat!\n");
		}
	}
	//for (int i = 0; i < model->vs.size(); ++i) {
	//	const IntVar v0 = model->vs[i];
	//	for (IntVarValues j(v0); j(); ++j) {

	//		for (int k = 0; k < model->vs.size(); ++k) {
	//			if (i != k) {
	//				const IntVar v1 = model->vs[k];
	//				for (IntVarValues l(v1); l(); ++l) {

	//					GModel *s = static_cast<GModel*>(model->clone());
	//					rel(*s, s->vs[i] == j.val());
	//					rel(*s, s->vs[k] == l.val());
	//					status = s->status();
	//					printf("(%d,%d,%d,%d):", i, j.val(), k, l.val());

	//					if (status == SS_BRANCH) {
	//						printf(" sat!\n");
	//					}
	//					else if (status == SS_SOLVED) {
	//						s->print();
	//					}
	//					else {
	//						printf(" unsat!\n");
	//					}

	//					//for (size_t m = 0; m < s->vs.size(); m++) {
	//					//	const IntVar v2 = s->vs[m];
	//					//	for (IntVarValues n(v2); n(); ++n)
	//					//		//bsd[i][j.val()][k][l.val()][m][n.val()] = 1;
	//					//	/*	printf()*/
	//					//}
	//					delete s;
	//				}
	//			}

	//		}
	//	}
	//}

	return true;
}
//
//bool SAC1::enforce() const {
//	bool modified = false;
//	SpaceStatus status = model->status();
//
//	if (status == SS_FAILED)
//		return false;
//
//	do {
//		modified = false;
//		for (int i = 0; i < model->vs.size(); i++) {
//			IntVar v = model->vs[i];
//
//			for (int j = v.min(); j <= v.max(); ++j) {
//				if (v.in(j)) {
//					GModel *s = static_cast<GModel*>(model->clone());
//					rel(*s, s->vs[i] == j);
//					status = s->status();
//					if (status == SS_FAILED) {
//						rel(*model, v != j);
//						status = model->status();
//						if (status == SS_FAILED) 
//							return false;
//
//						modified = true;
//					}
//					delete s;
//				}
//			}
//		}
//	} while (modified);
//
//	return true;
//}


//bool SAC1::enforce() const
//{
//	bool modified = false;
//	SpaceStatus status = model->status();
//	if (status == SS_FAILED)
//		return false;
//	do {
//		modified = false;
//		for (size_t i = 0; i < model->vs.size(); i++) {
//			IntVar v = model->vs[i];
//			for (IntVarValues j(v); j();) {
//				GModel *s = static_cast<GModel*>(model->clone());
//				const int a = j.val();
//				rel(*s, s->vs[i] == a);
//				status = s->status();
//				//s->print();
//				if (status == SS_FAILED) {
//					printf("(%d, %d) not sat sac!\n", i, a);
//					rel(*model, v != a);
//					status = model->status();
//					if (status == SS_FAILED) {
//						printf("failed\n");
//						return false;
//					}
//					modified = true;
//				}
//				else {
//					++j;
//				}
//				delete s;
//			}
//		}
//
//	} while (modified);
//
//	return true;
//}

} /* namespace cudacp */
