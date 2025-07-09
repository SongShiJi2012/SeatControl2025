%% Create enMemStopCause enum

classdef enMemStopCause < Simulink.IntEnumType

    enumeration
        EN_MemStop_NULL(0)
        EN_MemStop_Learn(1)
        EN_MemStop_OtherMove(2)
        EN_MemStop_HallErr(3)
        EN_MemStop_RelayErr(4)
        EN_MemStop_StallErr(5)
        EN_MemStop_NotON(6)
        EN_MemStop_NotGearPN(7)
        EN_MemStop_SpeedError(8)
        EN_MemStop_PosiError(9)
        EN_MemStop_ConfigError(10)
        EN_MemStop_NapError(11)
        EN_MemStop_MotorRunErr(12)
        EN_MemStop_EEPROMErr(13)
        EN_MemStop_VoltageErr(14)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemStopCause.EN_MemStop_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '记忆功能停止原因：&#10;0：无&#10;1：未学习&#10;2：座椅运动&#10;3：霍尔故障&#10;4：继电器粘连&#10;5：堵转故障&#10;6：非ON档&#10;7：档位非P/N&#10;8：车速故障&#10;9：位置错误&#10;10：记忆功能失能&#10;11：小憩模式打开&#10;12：电机运动&#10;13：e2p故障&#10;14：电压故障,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
