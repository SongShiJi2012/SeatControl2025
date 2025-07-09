%% Create enSeatHightMotorRunsts enum

classdef enSeatHightMotorRunsts < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_DnBkRelayAdhesion_FU(1)
        EN_ManualAdjust_FU(2)
        EN_AutoAdjust_FU(3)
        EN_DnBkRelayAdhesion_FU_Stop(4)
        EN_ManualAdjust_FU_Stop(5)
        EN_AutoAdjust_FU_Stop(6)
        EN_DnFURelayAdhesion_BK(7)
        EN_ManualAdjust_BK(8)
        EN_AutoAdjust_BK(9)
        EN_DnFURelayAdhesion_BK_Stop(10)
        EN_ManualAdjust_BK_Stop(11)
        EN_AutoAdjust_BK_Stop(12)
        EN_AutoAdjust_FUSuccess_Stop(13)
        EN_AutoAdjust_BKSuccess_Stop(14)
        EN_Timeout_Stop(15)
        EN_UpFn_Lock_Stop(16)
        EN_DnBa_Lock_Stop(17)
        EN_UpFn_Hall_Stop(18)
        EN_DnBa_Hall_Stop(19)
        EN_UpFn_MovTypeChange(20)
        EN_DnBa_MovTypeChange(21)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatHightMotorRunsts.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '电机动作类型：&#10;0：无动作；&#10;1：继电器下后粘连故障上前移动；&#10;2：手动开关有效上前移动；&#10;3：自动开关有效上前移动；&#10;4：继电器向下粘连故障恢复上前移动停止；&#10;5.手动开关无效上前移动停止&#10;6.自动调节开关无效上前移动停止&#10;7.继电器上前粘连故障下后移动&#10;8：手动开关有效上前移动；&#10;9：自动开关有效上前移动；&#10;A：继电器向下粘连故障恢复上前移动停止；&#10;B.手动开关无效上前移动停止&#10;C.手动开关无效上前移动停止&#10;D.自动调节开关无效上前移动停止&#10;E.自动调节开关无效下后移动停止&#10;F.超时停止&#10;10.向上堵转故障停止&#10;11.向下堵转故障停止&#10;12.向上霍尔故障停止&#10;13.向下霍尔故障停止,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
