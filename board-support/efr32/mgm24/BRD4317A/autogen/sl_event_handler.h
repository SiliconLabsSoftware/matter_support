#ifndef SL_EVENT_HANDLER_H
#define SL_EVENT_HANDLER_H

void sli_driver_permanent_allocation(void);
void sli_service_permanent_allocation(void);
void sli_stack_permanent_allocation(void);
void sli_internal_permanent_allocation(void);
void sl_platform_init(void);
void sli_internal_init_early(void);
void sl_kernel_start(void);
void sl_driver_init(void);
void sl_service_init(void);
void sl_stack_init(void);
void sl_internal_app_init(void);
void sl_iostream_init_instances_stage_1(void);
void sl_iostream_init_instances_stage_2(void);

#endif // SL_EVENT_HANDLER_H
