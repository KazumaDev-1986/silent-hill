#include "includes/app.h"

int main(void) {
  struct App *app = createApp();
  if (!app) {
    return 1;
  }

  runApp(app);
  destroyApp(&app);

  return 0;
}
