%% Create enWelStopCause enum

classdef enWelStopCause < Simulink.IntEnumType

    enumeration
        EN_WelStop_NULL(0)
        EN_WelStop_PRM(1)
        EN_WelStop_HallFault(2)
        EN_WelStop_RelayFault(3)
        EN_WelStop_LockFault(4)
        EN_WelStop_Busoff(5)
        EN_WelStop_OtherMove(6)
        EN_WelStop_enNotGearPN(7)
        EN_WelStop_enNotLearn(8)
        EN_WelStop_enBDCDoorLost(9)
        EN_WelStop_VoltageError(10)
        EN_WelStop_LengthMoveFaild(11)
        EN_WelStop_enBWMoveSuccess(12)
        EN_WelStop_enFWMoveSuccess(13)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enWelStopCause.EN_WelStop_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '迎宾功能座椅停止原因&#10;0x00: enNull 默认初始化状态&#10;0x01: enIVIPrmClose 功能配置关闭&#10;0x02: enHallFault 霍尔故障&#10;0x03: enLockFault堵转故障&#10;0x04: enRelayFault继电器故障&#10;0x05: enBusoff Busoff故障&#10;0x06: enOtherMove 高优先级动作中断&#10;0x07: enNotGearPN 非PN档&#10;0x08: enNotLearn 未学习&#10;0x09: enBDCDoorLost门状态报文掉线&#10;0x0A: enVoltageError电压不满足&#10;0x0B: enLengthMoveFaild 纵向移动反馈失败&#10;0x0C: enBWMoveSuccess 后移成功&#10;0x0D: enFWMoveSuccess 前移成功,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
