%% Create enVentStopReason enum

classdef enVentStopReason < Simulink.IntEnumType

    enumeration
        EN_VENT_STOP_R_NONE(0)
        EN_VENT_STOP_R_VOL(1)
        EN_VENT_STOP_R_FAULT(2)
        EN_VENT_STOP_R_CMD(3)
        EN_VENT_STOP_R_FACTORY(4)
        EN_VENT_STOP_R_TIME(5)
        EN_VENT_STOP_R_LOSS(6)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enVentStopReason.EN_VENT_STOP_R_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '通风禁能原因&#10;0：无禁能&#10;1：电压模式禁能&#10;2：存在故障&#10;3：互斥命令有效&#10;4：恢复出厂&#10;5：输出超时&#10;6：掉线禁能,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
