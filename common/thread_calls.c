/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   xrdp: A Remote Desktop Protocol server.
   Copyright (C) Jay Sorg 2004-2005

   thread calls

*/

#if defined(_WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif

/*****************************************************************************/
#if defined(_WIN32)
int
g_thread_create(unsigned long (__stdcall * start_routine)(void*), void* arg)
{
  DWORD thread;

  return !CreateThread(0, 0, start_routine, arg, 0, &thread);
}
#else
int
g_thread_create(void* (* start_routine)(void*), void* arg)
{
  pthread_t thread;
  int rv;

  rv = pthread_create(&thread, 0, start_routine, arg);
  pthread_detach(thread);
  return rv;
}
#endif

/*****************************************************************************/
int
g_get_threadid(void)
{
#if defined(_WIN32)
  return 0;
#else
  return pthread_self();
#endif
}