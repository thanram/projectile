#include "projectile.hpp"

const double m = 1;
const double g = 9.8066;
const double dt = 0.001;

auto force(TState s) { return VecR3<double>{0, -m * g}; }

auto euler_step(TState s, VecR3<double> accel) {
  TState next;
  next.t = s.t + dt;
  next.position = s.position + (s.velocity * dt);
  next.velocity = s.velocity + (accel * dt);
  return next;
}

auto euler_step(TState s, VecR3<double> accel) {
  TState next;
  next.t = s.t + dt;

  next.position = s.position + (s.velocity * dt) + .5*accel*dt*dt;
  next.accel = s.position;
  next.velocity = s.velocity + .5*(accel + next.accel)* dt;
  return next;
}



void n_steps(unsigned n, TState state0) {
  print_tstate(state0);
  if (n == 0)
    return;
  else {
    auto state = state0;
    for (unsigned k = 0; k < n; ++k) {
      state = euler_step(state, force(state) / m);
      print_tstate(state);
    }
  }
}

int main() {
  VecR3<double> position{-1/(pow(2,2)*sqrt(2)), 0, 0};
  VecR3<double> velocity{0, 1/(2*sqrt(2)), -.25};
  n_steps(1200, TState{0., {0, 0.1}, {5, 5}});


  return 0;
}