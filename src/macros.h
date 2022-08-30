// Created by LI Chaoran on 2019/05/29.
// Copyright © 2021 Bilibili. All rights reserved.

#ifndef CRON_BASE_MACROS_H_
#define CRON_BASE_MACROS_H_

#include <memory>

#define CRON_DISALLOW_COPY(TypeName) TypeName(const TypeName&) = delete

#define CRON_DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

#define CRON_DISALLOW_MOVE(TypeName) \
  TypeName(TypeName&&) = delete;     \
  TypeName& operator=(TypeName&&) = delete

#define CRON_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;           \
  TypeName& operator=(const TypeName&) = delete

#define CRON_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;                \
  TypeName(TypeName&&) = delete;                     \
  TypeName& operator=(const TypeName&) = delete;     \
  TypeName& operator=(TypeName&&) = delete

#define CRON_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                                \
  CRON_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName)

#define CRON_FORWARD_DECL(ClassName)                 \
  class ClassName;                                   \
  using ClassName##Ptr = std::shared_ptr<ClassName>; \
  using ClassName##WeakPtr = std::weak_ptr<ClassName>

#endif  // CRON_BASE_MACROS_H_
