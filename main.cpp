#include		<iostream>
#include		<cstdlib>
#include		"EnginesManagement.hh"

int			main(void)
{
  srandom(time(NULL));
  EnginesManagement	game;

  try
    {
      game.run();
    }
  catch (const std::exception& e)
    {
      std::cerr << "error: game system" << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
