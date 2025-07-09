%% Create enSystemVolt enum

classdef enSystemVolt < Simulink.IntEnumType

    enumeration
        EN_NORMAL(0)
        EN_STOP(1)
        EN_LOW(2)
        EN_HIGH(3)
        EN_OVER(4)
        EN_EXTREME(5)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSystemVolt.EN_NORMAL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '电机动作类型：&#10;0：正常；&#10;1：欠压；&#10;2：低压；&#10;3：高压；&#10;4：过压；&#10;5：极端电压,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
