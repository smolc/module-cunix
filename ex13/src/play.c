#include "filler.h"
#include "my_string.h"

int       is_free (elem_t *map, elem_t *el, pos_t pos)
{
  for(int i = 0; i < el->h; i++)
  {
    for(int j = 0; j < el->w; j++)
    {
      if(el->array[i][j] == '*')
      {
        if(i + pos.y < map->h && j + pos.x < map->w && i + pos.y >= 0 && j + pos.x >= 0)
        {
          if(map->array[i + pos.y][j + pos.x] != '.')
            return (0);
        }
        else
          return (0);
      }
    }
  }
  return (1);
};

int     is_connect (elem_t *map, elem_t *el, pos_t pos, char symbol)
{
  for(int i = 0; i < el->h; i++)
  {
    for(int j = 0; j < el->w; j++)
    {
      if(el->array[i][j] != '.')
      {
        if(i + pos.y + 1 < map->h && map->array[i + pos.y + 1][j + pos.x] == symbol)
          return (1);
        if(i + pos.y - 1 >= 0 && map->array[i + pos.y - 1][j + pos.x] == symbol)
          return (1);
        if(i + pos.x + 1 < map->w && map->array[i + pos.y][j + pos.x + 1] == symbol)
          return (1);
        if(i + pos.x - 1 >= 0 && map->array[i + pos.y][j + pos.x - 1] == symbol)
          return (1);
      }
    }
  }
  return (0);
};

pos_t       diagonals (req_t *core)
{
  static int   alg;
  pos_t        res;

  res.x = res.y = 0;
  if(alg == 0)
  {
    for(int i = 0; i < core->map.h; i++)
    {
      for(int j = 0; j < core->map.w; j++)
      {
        res.y = i;
        res.x = j;
        if(is_free(&(core->map), &(core->elem), res) && is_connect(&(core->map), &(core->elem), res, core->symbol))
        {
          if(res.x == 0)
            alg = 2;
          if(res.y == 0)
            alg = 1;
          return (res);
        }
      }
    }
  }

  if(alg == 1)
  {
    for(int i = core->map.h - 1; i >= 0; i--)
    {
      for(int j = 0; j < core->map.w; j++)
      {
        res.y = i;
        res.x = j;
        if(is_free(&(core->map), &(core->elem), res) && is_connect(&(core->map), &(core->elem), res, core->symbol))
        {
          if(res.x == 0)
            alg = 2;
          if(res.y == core->map.h - 1)
            alg = 0;
          return (res);
        }
      }
    }
  }

  if(alg == 2)
  {
    for(int i = core->map.h - 1; i >= 0; i--)
    {
      for(int j = core->map.w - 1; j >= 0; j--)
      {
        res.y = i;
        res.x = j;
        if(is_free(&(core->map), &(core->elem), res) && is_connect(&(core->map), &(core->elem), res, core->symbol))
        {
          if(res.x == core->map.w - 1)
            alg = 0;
          if(res.y == core->map.h - 1)
            alg = 1;
          return (res);
        }
      }
    }
  }
  return (res);
}

int     count_enemies (req_t *core, pos_t me)
{
  int     min_x, min_y, max_x, max_y;
  int     enemies;

  min_x = me.x - 2;
  min_y = me.y - 2;
  max_x = me.x + core->elem.w + 2;
  max_y = me.y + core->elem.h + 2;

  if(min_x < 0)
      min_x = 0;
  if(min_y < 0)
      min_y = 0;
  if(max_x >= core->map.w)
      max_x = core->map.w - 1;
  if(max_y >= core->map.h)
      max_y = core->map.h - 1;

  for(int i = min_y; i <= max_y; i++)
  {
    for(int j = min_x; j <= max_x; j++)
    {
      if(core->map.array[i][j] != '.' && core->map.array[i][j] != core->symbol)
      {
        enemies++;
      }
    }
  }
  return (enemies);
}

/* count enemies logic */
pos_t     logic (req_t *core)
{
  pos_t     res;
  int       enemies, cur_enemies;
  pos_t     temp;

  res.x = res.y  = 0;
  cur_enemies = enemies = 0;

  for(int i = 0; i < core->map.h; i++)
  {
    for(int j = 0; j < core->map.w; j++)
    {
      temp.y = i;
      temp.x = j;
      if(is_free(&(core->map), &(core->elem), temp) && is_connect(&(core->map), &(core->elem), temp, core->symbol))
      {
        cur_enemies = count_enemies(core, temp);
        if(cur_enemies > enemies)
        {
          enemies = cur_enemies;
          res.x = temp.x;
          res.y = temp.y;
        }
      }
    }
  }
  if(enemies < 4)
  {
    res = diagonals(core);
  }
  return (res);
}


pos_t     play (req_t *core)
{
  pos_t     res __attribute__((unused));

  mylogs("myfiller.log", "a", "(play.c -> play) Core->map.h: %d, Core->map.w: %d.\n", core->map.h, core->map.w);
  mylogs("myfiller.log", "a", "(play.c -> play) Core->elem.h: %d, Core->elem.w: %d.\n", core->elem.h, core->elem.w);

  res = logic(core);

  return (res);
};

